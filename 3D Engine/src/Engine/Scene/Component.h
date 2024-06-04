#pragma once
#include <glm/glm.hpp> 
#include "../RenderCore/Model.h"

namespace Engine
{

	class Entity;

	class Component
	{
	public:
		Component(Entity* entity) : m_ParentEntity(entity) {}

		Entity* GetParentEntity() const { return m_ParentEntity; }
	protected:
		template <typename T>
		inline static size_t GetGeneratedComponentID()
		{
			static size_t componentID = GenComponentID();
			return componentID;
		}

	private:
		inline static size_t GenComponentID()
		{
			static int componentCount = 0;
			size_t newComponentID = 1LL << componentCount++;


			return newComponentID;
		}
		
	private:
		Entity* m_ParentEntity;
	};

	class TagComponent : public Component
	{
	public:
		TagComponent(const std::string& tagName, Entity* entity): m_Tagname(tagName), Component(entity) {};

		std::string& GetTagName() { return m_Tagname; }
	public:
		static size_t GetComponenetID() { return GetGeneratedComponentID<TagComponent>(); }
	private:
		std::string m_Tagname;
	};

	class TransformComponent : public Component
	{
	public:
		TransformComponent() = default;

		TransformComponent(Entity* entity) : Component(entity) {}

		glm::mat4 GetTransform()
		{
			// Setting Transform
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, m_Position);
			// transform = glm::rotate()
			transform = glm::scale(transform, m_Scale);

			return transform;
		}

		static size_t GetComponenetID() { return GetGeneratedComponentID<TransformComponent>(); }

	public:
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
	private:
		
	};

	class MeshComponent : public Component
	{
	public:
		MeshComponent(std::string const& path, Entity* entity) : m_Model(path), Component(entity)
		{
		}


		Model m_Model;
	public:
		static size_t GetComponenetID() { return GetGeneratedComponentID<MeshComponent>(); }
	private:

	};


}