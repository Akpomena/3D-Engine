#pragma once

#include <Engine.h>
#include <map>

class SandBoxLayer: public Engine::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float ts) override;
	virtual void OnEvent(Event& event) override;
	virtual void OnImGuiRender() override;
private:
	std::unique_ptr<Camera> m_Camera;
	std::vector<std::unique_ptr<Engine::Mesh>> m_Mesh;
	std::vector<std::unique_ptr<Engine::Mesh>> m_Windows;
	std::unique_ptr<Shader> m_Shader[2];
	glm::vec4 m_ClearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
};

