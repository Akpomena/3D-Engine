#pragma once

#include <string>
#include <array>
#include <memory>
#include "./Shader.h"

namespace Engine
{
	class CubeMap
	{
	public:
		CubeMap(std::string path);
		void Draw();
		const unsigned int& GetCubeMapID() const { return m_CubeMapID; }
	private:
		unsigned int m_CubeMapID = 0;
		std::array<std::string, 6> m_Faces = {"right.jpg", "left.jpg", "bottom.jpg", "top.jpg", "front.jpg", "back.jpg"};

	};

}


