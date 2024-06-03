#pragma once

#include <string>
#include <array>
#include <memory>

#include "./VertexArray.h"
#include "./Shader.h"
#include "./Camera.h"

namespace Engine
{
	class SkyBox
	{
	public:
		SkyBox(std::string path);
		void Draw(Camera& camera);
		void Bind();
		const unsigned int& GetCubeMapID() const { return m_CubeMapID; }
	private:
		unsigned int m_CubeMapID = 0;
		std::array<std::string, 6> m_Faces = {"right.jpg", "left.jpg", "bottom.jpg", "top.jpg", "front.jpg", "back.jpg"};
		Shader m_SkyboxShader;
		VertexArray m_SkyboxVAO;
	};

}


