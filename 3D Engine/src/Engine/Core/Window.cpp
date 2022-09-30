#include "Window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

Window::Window(WindowProps props):
	m_Props(props), m_Window(nullptr)
{
	// TODO( GOOGLE THIS)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Init();
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}

	m_VSync = enabled;
}

bool Window::IsVSync() const
{
	return m_VSync;
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::enableCursor(bool enable)
{
	if (enable)
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


int Window::Init()
{
	if (!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		return -1;
	}

	m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), nullptr, nullptr);


	if (!m_Window)
	{
		std::cout << "FAILED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowUserPointer(m_Window, this);
	SetVSync(true);

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					currentWindow->m_EventFunction(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					currentWindow->m_EventFunction(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					currentWindow->m_EventFunction(event);
				}
			}
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					currentWindow->m_EventFunction(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					currentWindow->m_EventFunction(event);
					break;
				}
			}
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(xpos, ypos);
			currentWindow->m_EventFunction(event);
		});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(xoffset, yoffset);
			currentWindow->m_EventFunction(event);
		});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			currentWindow->m_EventFunction(event);
		});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			WindowResizeEvent event(width, height);
			currentWindow->m_EventFunction(event);
		});

	// Should be removed later
	glfwMakeContextCurrent(m_Window);

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return 0;
}

void Window::ShutDown()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
