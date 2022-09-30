#pragma once

#include <utility>

namespace Engine {

	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetPosition();
		static float GetXPos();
		static float GetYPos();
	};

}


