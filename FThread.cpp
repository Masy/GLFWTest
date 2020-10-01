/*
 * FThread.cpp
 *
 *  Created on: 29.01.2020
 *      Author: marce
 */

#include "FThread.hpp"
#include <iostream>


//---------------------------------------------------------------------------//
//                                Thread Class                               //
//---------------------------------------------------------------------------//

std::vector<FThread *> *FThread::INSTANCES = new std::vector<FThread *>();
std::mutex *FThread::INSTANCES_MUTEX = new std::mutex();

const std::chrono::duration<long, std::micro> MIN_OVERHEAD = std::chrono::microseconds(-2000);
const std::chrono::duration<long, std::micro> MAX_OVERHEAD = std::chrono::microseconds(2000);

FThread::FThread(const std::string &name, const double ticksPerSecond, const TaskQueueMode &taskQueueMode, const unsigned int taskQueueThreshold, const bool selfDestruct)
{
	this->m_name = name;
	this->m_thread = nullptr;
	this->m_waitingList = std::vector<FThread *>();
	this->m_frontTaskQueue = new std::queue<std::function<void()>>();
	this->m_backTaskQueue = new std::queue<std::function<void()>>();

	if (ticksPerSecond <= 0.0)
	{
		this->m_tps = -1.0;
		this->m_noSleepThread = true;
		this->m_sleepTime = std::chrono::microseconds(0);
	}
	else
	{
		this->m_tps = ticksPerSecond;
		this->m_noSleepThread = false;
		this->m_sleepTime = std::chrono::microseconds((int64_t) (1000000 / ticksPerSecond));
	}

	this->m_tickCount = 0;
	this->m_taskQueueThreshold = taskQueueThreshold;
	this->m_taskQueueMode = taskQueueMode;
	this->m_started = false;
	this->m_running = false;
	this->m_stopping = false;
	this->m_selfDestructing = selfDestruct;
	this->m_tickTime = 0;

	INSTANCES_MUTEX->lock();
	INSTANCES->push_back(this);
	INSTANCES_MUTEX->unlock();
}

FThread::~FThread()
{
	delete this->m_frontTaskQueue;
	delete this->m_backTaskQueue;
	delete this->m_thread;

	INSTANCES_MUTEX->lock();
	auto it = INSTANCES->begin();
	while (it != INSTANCES->end())
	{
		if ((*it) == this)
		{
			INSTANCES->erase(it);
			break;
		}

		it++;
	}
	INSTANCES_MUTEX->unlock();
}

std::thread *FThread::start(const unsigned int waitForSize, FThread **waitFor)
{
	this->m_started = true;
	this->m_stopping = false;
	if (waitForSize > 0)
	{
		this->m_waitingListMutex.lock();
		for (unsigned int n = 0; n < waitForSize; n++)
		{
			if (!waitFor[n]->m_running)
			{
				this->m_waitingList.push_back(waitFor[n]);
			}
		}
		this->m_waitingListMutex.unlock();
	}

	return new std::thread(&FThread::preStart, this);
}

void FThread::preStart()
{
	this->m_waitingListMutex.lock();
	bool isEmpty = this->m_waitingList.empty();
	this->m_waitingListMutex.unlock();

	while (!isEmpty)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		this->m_waitingListMutex.lock();
		isEmpty = this->m_waitingList.empty();
		this->m_waitingListMutex.unlock();
	}

	this->onStart();

	INSTANCES_MUTEX->lock();
	for (FThread *thread : *INSTANCES)
	{
		thread->removeFromWaitingList(this);
	}
	INSTANCES_MUTEX->unlock();

	this->run();
	this->onStop();

	this->m_started = false;
	this->m_stopping = false;
	if (this->m_selfDestructing)
	{
		delete this;
	}
}

void FThread::run()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTick = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTick = currentTick - this->m_sleepTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> sleepUntil;
	std::chrono::duration<long, std::micro> overhead = std::chrono::microseconds(0);
	std::chrono::duration<long, std::micro> duration = std::chrono::microseconds(0);
	this->m_running = true;

	if (this->m_taskQueueMode == QUEUE_ONLY)
	{
		bool isEmpty;
		while (this->m_running)
		{
			this->m_taskQueueMutex.lock();
			isEmpty = this->m_backTaskQueue->empty();
			this->m_taskQueueMutex.unlock();

			if (isEmpty)
			{
				std::this_thread::sleep_for(this->m_sleepTime);
			}
			else
			{
				this->processTaskQueue();
			}
		}
	}
	else
	{
		while (this->m_running)
		{
			if (this->m_noSleepThread)
			{
				currentTick = std::chrono::high_resolution_clock::now();
				duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTick - lastTick);
				lastTick = currentTick;

				if (this->m_taskQueueMode == QUEUE_ENABLED)
					this->processTaskQueue();

				this->m_tickTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTick.time_since_epoch()).count();

				this->onTick(this->m_tickTime, this->m_tickCount++);
			}
			else
			{
				currentTick = std::chrono::high_resolution_clock::now();

				duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTick - lastTick);

				this->m_sleepTimeMutex.lock();
				overhead += duration - this->m_sleepTime;

				if (overhead < MIN_OVERHEAD)
					overhead = MIN_OVERHEAD;
				else if (overhead > MAX_OVERHEAD)
					overhead = MAX_OVERHEAD;

				sleepUntil = currentTick + this->m_sleepTime - overhead;
				this->m_sleepTimeMutex.unlock();

				lastTick = currentTick;
				this->m_tickTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTick.time_since_epoch()).count();

				if (this->m_taskQueueMode == QUEUE_ENABLED)
					this->processTaskQueue();

				this->onTick(this->m_tickTime, this->m_tickCount++);

				std::this_thread::sleep_until(sleepUntil);
			}
		}
	}
}

void FThread::stop()
{
	this->m_stopping = true;
	this->m_running = false;
}

void FThread::processTaskQueue()
{
	this->m_taskQueueMutex.lock();
	if (this->m_backTaskQueue->size() > this->m_taskQueueThreshold)
		std::cout << "[" << this->m_name << "][WARNING]: task queue is bigger than the threshold: " << this->m_backTaskQueue->size() << "/"
				  << this->m_taskQueueThreshold << "!" << std::endl;

	std::queue<std::function<void()>> *tmp = this->m_frontTaskQueue;
	this->m_frontTaskQueue = this->m_backTaskQueue;
	this->m_backTaskQueue = tmp;
	this->m_taskQueueMutex.unlock();

	while (!this->m_frontTaskQueue->empty())
	{
		this->m_frontTaskQueue->front()();
		this->m_frontTaskQueue->pop();
	}
}

void FThread::addTask(const std::function<void()> &task)
{
	if (this->m_running && this->m_taskQueueMode != QUEUE_DISABLED)
	{
		this->m_taskQueueMutex.lock();
		this->m_backTaskQueue->push(task);
		this->m_taskQueueMutex.unlock();
	}
}

void FThread::removeFromWaitingList(FThread *thread)
{
	this->m_waitingListMutex.lock();
	auto iterator = this->m_waitingList.begin();
	while (iterator != this->m_waitingList.end())
	{
		if (*iterator == thread)
		{
			this->m_waitingList.erase(iterator);
			break;
		}
	}
	this->m_waitingListMutex.unlock();
}

const std::string *FThread::getName() const
{
	return &this->m_name;
}

bool FThread::hasStarted() const
{
	return this->m_started;
}

bool FThread::isRunning() const
{
	return this->m_running;
}

bool FThread::isStopping() const
{
	return this->m_stopping;
}

double FThread::getTicksPerSecond() const
{
	return this->m_tps;
}

void FThread::setTicksPerSecond(const double newTPS)
{
	this->m_tps = newTPS <= 0.0 ? -1.0 : newTPS;
	if (this->m_tps == -1.0)
		this->m_noSleepThread = true;
	else
	{
		this->m_noSleepThread = false;
		this->m_sleepTimeMutex.lock();
		this->m_sleepTime = std::chrono::microseconds(static_cast<int64_t>(1000000 / this->m_tps));
		this->m_sleepTimeMutex.unlock();
	}
}

unsigned long FThread::getTickCount() const
{
	return this->m_tickCount;
}

unsigned long FThread::getCurrentTime() const
{
	return this->m_tickTime;
}
