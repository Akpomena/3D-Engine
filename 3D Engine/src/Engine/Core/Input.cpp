#include "Input.h"

#include <GLFW/glfw3.h>
#include "./Application.h"

bool Engine::Input::IsKeyPressed(int keycode)
{
	auto window = Application::Get().GetWindow().GetWindow();
	auto state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Engine::Input::IsMouseButtonPressed(int button)
{
	auto window = Application::Get().GetWindow().GetWindow();
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

std::pair<float, float> Engine::Input::GetPosition()
{
	auto window = Application::Get().GetWindow().GetWindow();

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return { (float)xPos, (float)yPos };
}

float Engine::Input::GetXPos()
{
	auto [x, y] = GetPosition();
	return x;
}

float Engine::Input::GetYPos()
{
	auto [x, y] = GetPosition();
	return y;
}
