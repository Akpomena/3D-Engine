#include "Scene.h"

#include "Entity.h"

#include "Component.h"

#include "../Renderer/Renderer.h"

Engine::Scene::Scene(const char* sceneName, const char* skybox) : m_SceneName(sceneName), m_Skybox(skybox)
{
}

void Engine::Scene::DrawScene()
{
	/*for (auto& [key, entity] : m_Entities)
	{
		if (entity.HasComponent[MeshComponent::GetComponenetID()])
		{
			MeshComponent* newModel = (MeshComponent*)entity.m_Components[MeshComponent::GetComponenetID()];

			TransformComponent* newTransform = (TransformComponent*)entity.m_Components[TransformComponent::GetComponenetID()];


			for (int i = 0; i < newModel->m_Model.GetMeshes().size(); i++)
			{
				Renderer::Draw(newModel->m_Model.GetMeshes()[i], newTransform->GetTransform());
			}
		}
	}*/

	for (auto mesh : GetComponents<MeshComponent>())
	{
		for (int i = 0; i < mesh->m_Model.GetMeshes().size(); i++)
		{
			TransformComponent* transform = mesh->GetParentEntity()->GetComponent<TransformComponent>();
			Renderer::Draw(mesh->m_Model.GetMeshes()[i], transform->GetTransform());
		}
	}
}
Engine::Entity& Engine::Scene::GetEntity(const std::string& name)
{
	if (m_Entities.find(name) == m_Entities.end())
	{
		assert(false, "Entity does already exist");
	}

	return m_Entities[name];
}

void Engine::Scene::CreateEntity(std::string const& entityName)
{

	if (m_Entities.find(entityName) != m_Entities.end())
	{
		assert(false, "Entity already exists");
	}


	m_Entities.emplace(std::piecewise_construct, std::forward_as_tuple(entityName), std::forward_as_tuple(entityName,this));
}
