#pragma once

#include <string>
#include <vector>
#include "Entity.h"

namespace Engine
{
	class Scene
	{
	public:
		Scene() = default;
		Scene(std::string& sceneName);
		void DrawScene();

		Entity* GetEntity(int id);
		Entity* CreateEntity(std::string const& entityName = "New Entity");
	private:
		std::string m_SceneName = std::string();
		std::vector<Entity*> m_Entities;
	};

}

