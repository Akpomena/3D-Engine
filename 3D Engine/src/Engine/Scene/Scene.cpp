#include "Scene.h"

#include "Entity.h"

#include "Component.h"

#include "../Renderer/Renderer.h"

Engine::Scene::Scene(std::string& sceneName) : m_SceneName(sceneName)
{
}

void Engine::Scene::DrawScene()
{
	for (auto entity : m_Entities)
	{
		MeshComponent* newModel = (MeshComponent*)entity->m_Components[MeshComponent::GetComponenetID()];

		TransformComponent* newTransform = (TransformComponent*)entity->m_Components[TransformComponent::GetComponenetID()];


		for (int i = 0; i < newModel->m_Model.GetMeshes().size(); i++)
		{
			Renderer::Draw(newModel->m_Model.GetMeshes()[i], newTransform->GetTransform());
		}
	}
}

Engine::Entity* Engine::Scene::CreateEntity(std::string const& entityName)
{
	Entity* entity = new Entity(entityName);
	/*m_Entities.push_back(Entity(entityName));*/
	entity->AddComponent<TransformComponent>(new TransformComponent());

	m_Entities.push_back(entity);

	return entity;
}
