#pragma once

struct GLFWwindow;

class ImguiManager
{
public:
	ImguiManager() = default;
	~ImguiManager();

	void init(GLFWwindow* window);
	void BeginDraw();
	void EndDraw();
private:
};

