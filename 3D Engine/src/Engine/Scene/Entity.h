#pragma once

#include <string>
#include <unordered_map>
#include "Component.h"

namespace Engine
{
	class Entity
	{
	public:
		Entity(std::string const& entityName): m_EntityName(entityName)
		{}

		template<typename T>
		bool HasComponent()
		{
			return m_Components & T::GetComponentID();
		}

		template <typename T>
		void AddComponent(T* component) 
		{
			m_Components[T::GetComponenetID()] = std::move(component);
			m_AvailableComponents = m_AvailableComponents | T::GetComponenetID();
		}

		std::unordered_map<size_t, Component*> m_Components; // TODO(Remove this)
	private:
		size_t m_EntityID;
		std::string m_EntityName;
		size_t m_AvailableComponents = 0;
	};



}

