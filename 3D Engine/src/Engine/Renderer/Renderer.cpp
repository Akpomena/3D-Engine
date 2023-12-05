#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <assert.h>

Shader* Engine::Renderer::m_Shader = nullptr;

void Engine::Renderer::Init()
{
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	assert(status);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Engine::Renderer::BeginScene(Camera& camera, Shader& shader)
{
	m_Shader = &shader;

	m_Shader->SetUniformMat4("u_Projection", camera.GetProjMatrix());
	m_Shader->SetUniformMat4("u_View", camera.GetViewMatrix());
}

void Engine::Renderer::EndScene()
{
	Clear();
}

void Engine::Renderer::Draw(Mesh& mesh)
{
	mesh.Draw(*m_Shader);
}

void Engine::Renderer::SetClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void Engine::Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
