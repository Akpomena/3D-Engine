#pragma once

#include <string>
#include <vector>
#include "Entity.h"

#include "../RenderCore/CubeMap.h"

namespace Engine
{
	class Scene
	{
	public:
		Scene() = default;
		Scene(const char* sceneName, const char* skybox);
		void DrawScene();
		void DrawSkyBox(Camera& camera) { m_Skybox.Draw(camera); }

		Entity* GetEntity(int id) {}
		Entity* CreateEntity(std::string const& entityName = "New Entity");
	private:
		std::string m_SceneName = std::string();
		std::vector<Entity*> m_Entities;
		SkyBox m_Skybox;
	};

}

