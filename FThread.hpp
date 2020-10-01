/*
 * FThread.hpp
 *
 *  Created on: 29.01.2020
 *      Author: marce
 */

#ifndef CORE_CONCURRENT_FTHREAD_HPP_
#define CORE_CONCURRENT_FTHREAD_HPP_

#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>

/**
 * Enum defining how an FThread will handle the task queue.
 */
enum TaskQueueMode
{
	/**
	 * The task queue will be processed before the onTick() method is called.
	 */
	QUEUE_ENABLED,
	/**
	 * Only the task queue will be processed.
	 */
	QUEUE_ONLY,
	/**
	 * The task queue will not be processed at all.
	 */
	QUEUE_DISABLED
};

/**
 * Class representing a thread with advanced features.
 */
class FThread
{
protected:

	/**
	 * List with pointers to all FThreads.
	 */
	static std::vector<FThread *> *INSTANCES;
	/**
	 * Mutex for the {@link #INSTANCES} list.
	 */
	static std::mutex *INSTANCES_MUTEX;

	/**
	 * The name of the thread.
	 */
	std::string m_name;
	/**
	 * A pointer to the std::thread this FThread is wrapped around.
	 */
	std::thread *m_thread;
	/**
	 * A list with pointers to the FThreads this FThread is waiting for before starting.
	 */
	std::vector<FThread *> m_waitingList;
	/**
	 * Mutex for the {@link #m_waitingList} list.
	 */
	std::mutex m_waitingListMutex;
	/**
	 * A pointer to the front task queue that will be processed when {@link #processTaskQueue()} is called.
	 */
	std::queue<std::function<void()>> *m_frontTaskQueue;
	/**
	 * A pointer to the back task queue where new tasks will be added to when {@link #addTask()} is called.
	 */
	std::queue<std::function<void()>> *m_backTaskQueue;
	/**
	 * Mutes for the {@link #m_backTaskQueue} queue.
	 */
	std::mutex m_taskQueueMutex;
	/**
	 * The threshold of the task queue.
	 *
	 * <p>If the size of {@link #m_backTaskQueue} is greater than this when {@link #processTaskQueue} is called a warning will be printed.</p>
	 */
	unsigned int m_taskQueueThreshold;
	/**
	 * The mode of the task queue which defines how it is handled.
	 *
	 * @see #TaskQueueMode for a detailed description.
	 */
	TaskQueueMode m_taskQueueMode;
	/**
	 * The ticks per second this FThread tries to achieve.
	 */
	double m_tps;
	/**
	 * The average sleep time this FThread has to achieve the needed tps defined in {@link #m_tps}.
	 */
	std::chrono::duration<long, std::micro> m_sleepTime;
	/**
	 * The mutex of the sleep time.
	 */
	std::mutex m_sleepTimeMutex;
	/**
	 * Whether the thread does not sleep or sleep.
	 */
	std::atomic_bool m_noSleepThread;
	/**
	 * The amount of ticks the FThread has ticked.
	 */
	std::atomic_ulong m_tickCount;
	/**
	 * The time of the current tick in milliseconds;
	 */
	std::atomic_ulong m_tickTime;
	/**
	 * Whether the FThread has started or not.
	 */
	std::atomic_bool m_started;
	/**
	 * Whether the FThread is running or not.
	 */
	std::atomic_bool m_running;
	/**
	 * Whether the FThread is stopping or not.
	 */
	std::atomic_bool m_stopping;
	/**
	 * Whether the thread destroys itself when it has stopped or not.
	 */
	bool m_selfDestructing;

	/**
	 * Method which will be the start method of the {@link #m_thread}.
	 */
	void preStart();

	/**
	 * The main loop of the FThread.
	 */
	void run();

	/**
	 * Method which is called when the FThread is about to start.
	 */
	virtual void onStart() = 0;

	/**
	 * Method which is called every tick.
	 *
	 * @param currentTime The current time in milliseconds.
	 * @param currentTick The current tick.
	 */
	virtual void onTick(unsigned long currentTime, unsigned long currentTick) = 0;

	/**
	 * Method which is called when the FThread is about to stop.
	 */
	virtual void onStop() = 0;

	/**
	 * Removes the given FThread from the waiting list of this FThread.
	 *
	 * @param thread A pointer to the {@link FThread} that will be removed from this FThread's waiting list.
	 */
	void removeFromWaitingList(FThread *thread);

	/**
	 * Processes the task queue of the FThread.
	 */
	void processTaskQueue();

public:
	/**
	 * Constructs a new FThread.
	 *
	 * @param name A reference to the name of the thread.
	 * @param ticksPerSecond The ticks per second the FThread tries to achieve.
	 * @param queueExecutionOrder A reference to the {@link TaskQueueMode} of the FThread.
	 * @param taskQueueThreshold The threshold of the task queue.
	 * @param selfDestruct Whether the thread deletes itself when it stopped or not.
	 */
	explicit FThread(const std::string &name, double ticksPerSecond = 50.0, const TaskQueueMode &queueExecutionOrder = QUEUE_ENABLED,
			unsigned int taskQueueThreshold = 250, bool selfDestruct = false);

	/**
	 * Destroys the FThread.
	 */
	virtual ~FThread();

	/**
	 * Starts the FThread.
	 *
	 * @param waitForSize The number of FThreads this FThread is waiting for before actually starting.
	 * @param waitFor A pointer array to the FThreads this FThread is waiting for.
	 *
	 * @return the std::thread this FThread is wrapped around.
	 */
	std::thread *start(unsigned int waitForSize = 0, FThread **waitFor = nullptr);

	/**
	 * Adds a task to the task queue of the FThread.
	 *
	 * @param task The task that will be added to the queue of this FThread.
	 */
	void addTask(const std::function<void()> &task);

	/**
	 * Stops the FThread.
	 */
	void stop();

	/**
	 * Gets the name of the FThread.
	 *
	 * @return a const pointer to the name of the FThread.
	 */
	[[nodiscard]] const std::string *getName() const;

	/**
	 * Gets whether this FThread has started or not.
	 *
	 * @return <code>true</code> when the FThread has started already.
	 */
	[[nodiscard]] bool hasStarted() const;

	/**
	 * Gets whether this FThread is running or not.
	 *
	 * @return <code>true</code> when the FThread is running.
	 */
	[[nodiscard]] bool isRunning() const;

	/**
	 * Gets whether this FThread is stopping or not.
	 *
	 * @return <code>true</code> when the FThread is stopping.
	 */
	[[nodiscard]] bool isStopping() const;

	/**
	 * Gets the ticks per second this FThread tries to achieve.
	 *
	 * @return the ticks per second this FThread tries to achieve.
	 */
	[[nodiscard]] double getTicksPerSecond() const;

	/**
	 * Sets the ticks per second this FThread tries to achieve.
	 *
	 * @param newTPS The new ticks per second the FThread tries to achieve.
	 */
	void setTicksPerSecond(double newTPS);

	/**
	 * Gets the tick count of this FThread.
	 *
	 * @return the tick count if this FThread.
	 */
	[[nodiscard]] unsigned long getTickCount() const;

	/**
	 * Gets the time of the current tick in milliseconds.
	 *
	 * @return the time of the current tick in milliseconds.
	 */
	[[nodiscard]] unsigned long getCurrentTime() const;
};


#endif /* CORE_CONCURRENT_FTHREAD_HPP_ */
