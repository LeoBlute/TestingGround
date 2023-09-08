#include "Window.hpp"
#include "Application.hpp"
#include "Glad/glad.h"
#include "GLFW/include/glfw3.h"
#include <iostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

static inline GLFWwindow* rawWindow;

static inline void CloseCallback(GLFWwindow* window)
{
	Application::Quit();
};

bool Window::Init()
{
	if (!glfwInit()) [[unlikely]]
	{
		std::cout << "Glad could not initialize" << std::endl;
		return false;
	};
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);

	rawWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "App", NULL, NULL);

	glfwMakeContextCurrent(rawWindow);
	glfwSetWindowCloseCallback(rawWindow, CloseCallback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) [[unlikely]]
	{
		std::cout << "Glad could not initialize" << std::endl;
		return false;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(rawWindow,
		[](GLFWwindow* window, int width, int height)
		{ glViewport(0, 0, width, height); });

	return true;
}
void Window::Terminate()
{
	glfwTerminate();
}
void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(rawWindow);
}

void Window::ClearScreen()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::ProcessInputs()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(rawWindow);
}

void* Window::GetRawWindow()
{
	return rawWindow;
}

int Window::GetWidth()
{
	int width;
	glfwGetWindowSize(rawWindow, &width, NULL);
	return width;
}

int Window::GetHeight()
{
	int height;
	glfwGetWindowSize(rawWindow, NULL, &height);
	return height;
}

int Window::GetXPos()
{
	int xpos;
	glfwGetWindowPos(rawWindow, &xpos, NULL);
	return xpos;
}

int Window::GetYPos()
{
	int ypos;
	glfwGetWindowPos(rawWindow, NULL, &ypos);
	return ypos;
}

void Window::SetSize(float width, float height)
{
	glfwSetWindowSize(rawWindow, width, height);
}