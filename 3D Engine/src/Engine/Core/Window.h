#pragma once

#include <functional>
#include "../Events/Event.h"

struct GLFWwindow;

struct WindowProps
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProps(const std::string& title = "Engine",
		unsigned int width = 800,
		unsigned int height = 600)
		:Title(title), Width(width), Height(height)
	{

	}
};

class Window
{
public:
	Window(WindowProps props);

	void SetEventCallback(const std::function<void(Event&)>& eventFunc) { m_EventFunction = eventFunc; }
	GLFWwindow* GetWindow() { return m_Window; }
	void Update();
	void EnableCursor(bool enable);
	void SetViewPort(int width, int height);

	unsigned int GetWidth() { return m_Props.Width; }
	unsigned int GetHeight() { return m_Props.Height; }

	void SetVSync(bool enable);
	bool IsVSync() const;

	int Init();
	void ShutDown();
private:
	GLFWwindow* m_Window;
	bool m_VSync = true;
	WindowProps m_Props;
	std::function<void(Event&)> m_EventFunction;
};

