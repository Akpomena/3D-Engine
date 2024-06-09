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
			tempComponent.reserve(m_Components[T::GetComponentID()].size());

			for (auto component : m_Components[T::GetComponentID()])
			{
				tempComponent.push_back((T*)component);
			}

			return tempComponent;
		}

	private:
		template<typename T>
		T* GetComponent(size_t& index)
		{
			return static_cast<T*>(m_Components[T::GetComponentID()][index]);
		}
	private:
		std::string m_SceneName = std::string();
		std::map<std::string, Entity> m_Entities;
		std::map<size_t, std::vector<Component*>> m_Components;
		SkyBox m_Skybox;

		friend class Entity;
	};

}

