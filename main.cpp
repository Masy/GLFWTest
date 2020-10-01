#include <iostream>
#include <thread>
#include <future>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#ifdef WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include "GLFW/glfw3native.h"
#include "FThread.hpp"


//#define POLL_EVENTS_IN_MAIN


const char *vertexShaderSource = R"glsl(
#version 330

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec3 v_color;

out vec3 f_color;

void main()
{
	gl_Position = vec4(v_position, 1.0, 1.0);
	f_color = v_color;
}

)glsl";

const char *fragmentShaderSource = R"glsl(
#version 330

layout (location = 0) out vec4 fragmentColor;

in vec3 f_color;

void main()
{
	fragmentColor = vec4(f_color, 1.0f);
}

)glsl";

struct Model
{
	uint32_t vaoId;
	uint32_t vboId;
	uint32_t vertexShader;
	uint32_t fragmentShader;
	uint32_t program;
};

class WindowThread1 : public FThread
{
private:

	GLFWwindow *window;

	Model model;

public:

	WindowThread1() : FThread("WindowThread1", 60, QUEUE_ENABLED, 250, true)
	{
		this->window = nullptr;
		this->model = {0, 0, 0, 0, 0};
	}

	void onStart() override
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		this->window = glfwCreateWindow(640, 480, "Window 1", nullptr, nullptr);

		glfwSetWindowUserPointer(this->window, this);

		glfwSetCursorPosCallback(window, [] (GLFWwindow *glfwWindow, double posX, double posY) {
			auto *thread = reinterpret_cast<WindowThread1*>(glfwGetWindowUserPointer(glfwWindow));
			glfwMakeContextCurrent(glfwWindow);
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(thread->model.program);
			glBindVertexArray(thread->model.vaoId);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			glBindVertexArray(0);

			/* Swap front and back buffers */
			glfwSwapBuffers(glfwWindow);
		});

		glfwSetWindowCloseCallback(this->window, [] (GLFWwindow *glfwWindow) {
			reinterpret_cast<WindowThread1*>(glfwGetWindowUserPointer(glfwWindow))->stop();
		});

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glfwSwapInterval(1);

		glGenVertexArrays(1, &this->model.vaoId);
		glBindVertexArray(this->model.vaoId);

		float data[] = {0.0f, 0.5f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f};

		glGenBuffers(1, &this->model.vboId);
		glBindBuffer(GL_ARRAY_BUFFER, this->model.vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 15, data, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 5, (const void *) (sizeof(float) * 2));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		this->model.vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->model.vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(this->model.vertexShader);

		this->model.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->model.fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(this->model.fragmentShader);

		this->model.program = glCreateProgram();
		glAttachShader(this->model.program, this->model.vertexShader);
		glAttachShader(this->model.program, this->model.fragmentShader);
		glLinkProgram(this->model.program);

		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);

		glViewport(0, 0, 640, 480);
	}

	void onTick(const unsigned long currentTime, const unsigned long currentTick) override
	{
#ifndef POLL_EVENTS_IN_MAIN
		glfwPollEvents();
#endif
	}

	void onStop() override
	{
		glDeleteVertexArrays(1, &this->model.vaoId);
		glDeleteBuffers(1, &this->model.vboId);

		glDeleteShader(this->model.vertexShader);
		glDeleteShader(this->model.fragmentShader);

		glDeleteProgram(this->model.program);

		glfwDestroyWindow(this->window);
	}
};

class WindowThread2 : public FThread
{
private:

	GLFWwindow *window;

	Model model;

public:

	WindowThread2() : FThread("WindowThread2", 60, QUEUE_ENABLED, 250, true)
	{
		this->window = nullptr;
		this->model = {0, 0, 0, 0, 0};
	}

	void onStart() override
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		this->window = glfwCreateWindow(640, 480, "Window 2", nullptr, nullptr);

		glfwSetWindowUserPointer(this->window, this);

		glfwSetCursorPosCallback(window, [] (GLFWwindow *glfwWindow, double posX, double posY) {
			auto *thread = reinterpret_cast<WindowThread2*>(glfwGetWindowUserPointer(glfwWindow));
			glfwMakeContextCurrent(glfwWindow);
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(thread->model.program);
			glBindVertexArray(thread->model.vaoId);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			glBindVertexArray(0);

			/* Swap front and back buffers */
			glfwSwapBuffers(glfwWindow);
		});

		glfwSetWindowCloseCallback(this->window, [] (GLFWwindow *glfwWindow) {
			reinterpret_cast<WindowThread2*>(glfwGetWindowUserPointer(glfwWindow))->stop();
		});

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		gladLoadGL();

		glGenVertexArrays(1, &this->model.vaoId);
		glBindVertexArray(this->model.vaoId);

		float data[] = {0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

		glGenBuffers(1, &this->model.vboId);
		glBindBuffer(GL_ARRAY_BUFFER, this->model.vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 15, data, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 5, (const void *) (sizeof(float) * 2));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		this->model.vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->model.vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(this->model.vertexShader);

		this->model.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->model.fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(this->model.fragmentShader);

		this->model.program = glCreateProgram();
		glAttachShader(this->model.program, this->model.vertexShader);
		glAttachShader(this->model.program, this->model.fragmentShader);
		glLinkProgram(this->model.program);

		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);

		glViewport(0, 0, 640, 480);
	}

	void onTick(const unsigned long currentTime, const unsigned long currentTick) override
	{
#ifndef POLL_EVENTS_IN_MAIN
		glfwPollEvents();
#endif
	}

	void onStop() override
	{
		glDeleteVertexArrays(1, &this->model.vaoId);
		glDeleteBuffers(1, &this->model.vboId);

		glDeleteShader(this->model.vertexShader);
		glDeleteShader(this->model.fragmentShader);

		glDeleteProgram(this->model.program);
		glfwDestroyWindow(this->window);
	}
};

int main()
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	auto a1 = new WindowThread1();
	auto a2 = new WindowThread2();

	auto *thread1 = a1->start();
	auto *thread2 = a2->start();

#ifdef POLL_EVENTS_IN_MAIN
	while (a1->isRunning() || a2->isRunning())
	{
		glfwPollEvents();
	}
#endif

	thread1->join();
	thread2->join();
	glfwTerminate();
	return 0;
}
