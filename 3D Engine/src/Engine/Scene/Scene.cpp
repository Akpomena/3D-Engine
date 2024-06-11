#include "Scene.h"

#include "Entity.h"

#include "Component.h"

#include "../Renderer/Renderer.h"
#include "../Debug/Instrumentor.h"

Engine::Scene::Scene(const char* sceneName, const char* skybox) : m_SceneName(sceneName), m_Skybox(skybox)
{
}

void Engine::Scene::DrawScene()
{
	PROFILE_FUNCTION();

	for (auto& meshComponent : GetComponents<MeshComponent>())
	{
		TransformComponent* transformComponent = meshComponent->GetParentEntity()->GetComponent<TransformComponent>();
		glm::mat4 transform = transformComponent->GetTransform();

		for (auto& mesh: meshComponent->m_Model.GetMeshes())
		{
			Renderer::Draw(mesh, transform);
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
