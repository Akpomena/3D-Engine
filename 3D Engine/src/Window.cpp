#include "Window.h"

#include <iostream>

#include "./Events/ApplicationEvent.h"
#include "./Events/KeyEvent.h"
#include "./Events/MouseEvent.h"

Window::Window(const char* windowName, int width, int height): m_Height(height), m_Width(width), m_Window(nullptr)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Init();
}

void Window::UpdateWindow()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

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

	m_Window = glfwCreateWindow(m_Width, m_Height, "3D Engine", nullptr, nullptr);


	if (!m_Window)
	{
		std::cout << "FAILED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowUserPointer(m_Window, this);

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
		{
			Window currentWindow = *static_cast<Window*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					currentWindow.m_EventFunction(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					currentWindow.m_EventFunction(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					currentWindow.m_EventFunction(event);
				}
			}
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			Window currentWindow = *static_cast<Window*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					currentWindow.m_EventFunction(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					currentWindow.m_EventFunction(event);
					break;
				}
			}
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			Window currentWindow = *static_cast<Window*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(xpos, ypos);
			currentWindow.m_EventFunction(event);
		});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			Window currentWindow = *static_cast<Window*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(xoffset, yoffset);
			currentWindow.m_EventFunction(event);
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
