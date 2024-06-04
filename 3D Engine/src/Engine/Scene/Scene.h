#pragma once

#include <string>
#include <map>
#include <vector>


#include "../RenderCore/CubeMap.h"

namespace Engine
{
	class Entity;
	class Component;

	class Scene
	{
	public:
		Scene() = default;
		Scene(const char* sceneName, const char* skybox);
		void DrawScene();
		void DrawSkyBox(Camera& camera) { m_Skybox.Draw(camera); }

		Entity& GetEntity(const std::string& name);
		void CreateEntity(std::string const& entityName);

		template<typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> tempComponent;
			tempComponent.reserve(m_Components[T::GetComponenetID()].size());

			for (auto component : m_Components[T::GetComponenetID()])
			{
				tempComponent.push_back((T*)component);
			}

			return tempComponent;
		}

	private:
		std::string m_SceneName = std::string();
		std::map<std::string, Entity> m_Entities;
		std::map<size_t, std::vector<Component*>> m_Components;
		SkyBox m_Skybox;

		friend class Entity;
	};

}

