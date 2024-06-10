#pragma once

#include <string>
#include <unordered_map>
#include "Component.h"

#include "./Scene.h"

namespace Engine
{

	class Scene;

	class Entity
	{
	public:
		Entity(std::string const& entityName, Scene* scene): m_EntityName(entityName), m_Scene(scene)
		{
			this->AddComponent<TagComponent>(new TagComponent(entityName, this));
			this->AddComponent<TransformComponent>(new TransformComponent(this));
		}

		Entity() = default;

		template<typename T>
		bool HasComponent()
		{
			return m_AvailableComponents & T::GetComponentID();
		}

		template<typename T>
		T* GetComponent()
		{
			size_t index = m_Components[T::GetComponentID()];
			return m_Scene->GetComponent<T>(index);
		}
		
		template <typename T>
		void AddComponent(T* component) 
		{
			size_t index = m_Scene->m_Components[T::GetComponentID()].size();
			m_Scene->m_Components[T::GetComponentID()].push_back(component);

			m_Components[T::GetComponentID()] = index;
			m_AvailableComponents = m_AvailableComponents | T::GetComponentID();
		}

	private:
		std::unordered_map<size_t, size_t> m_Components;
		size_t m_EntityID = 0;
		std::string m_EntityName;
		size_t m_AvailableComponents = 0;
		Scene* m_Scene;
	};



}

