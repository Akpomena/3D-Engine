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
		bool HasComponent() const
		{
			return m_Components & T::GetComponentID();
		}

		template <typename T>
		void AddComponent(T* component) 
		{
			m_Components[T::GetComponenetID()] = component;
			m_AvailableComponents = m_AvailableComponents | T::GetComponenetID();

			m_Scene->m_Components[T::GetComponenetID()].push_back(component);
		}

		std::unordered_map<size_t, Component*> m_Components; // TODO(Remove this)
	private:
		size_t m_EntityID;
		std::string m_EntityName;
		size_t m_AvailableComponents = 0;
		Scene* m_Scene;
	};



}

