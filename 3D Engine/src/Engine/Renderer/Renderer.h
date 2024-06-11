#pragma once

#include <glm/glm.hpp>

#include "../RenderCore/Camera.h"
#include "../RenderCore/Mesh.h"
#include "../RenderCore/Shader.h"

namespace Engine {

	struct  RendererStats
	{
		int renderCalls = 0;
	};
	
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(Camera& camera, Shader& shader);
		static void EndScene();
		static void Draw(Mesh& mesh, glm::mat4& transform);
		static void SetClearColor(glm::vec4 color);

		static const RendererStats* GetStats() { return m_Stats; }
	
	public:
		static Shader* m_Shader;
		static void Clear();
		static RendererStats* m_Stats;
	};
}


