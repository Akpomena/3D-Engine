#pragma once

#include "GlFW/glfw3.h"
#include <functional>
#include "./Events/Event.h"

class Window
{
public:
	Window(const char* windowName, int height, int wodth);

	void SetEventCallback(const std::function<void(Event&)>& eventFunc) { m_EventFunction = eventFunc; }
	GLFWwindow* GetWindow() { return m_Window; }
	void UpdateWindow();
	void enableCursor(bool enable);

	int Init();
	void ShutDown();
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
	std::function<void(Event&)> m_EventFunction;
};

