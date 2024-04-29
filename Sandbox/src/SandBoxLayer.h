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
	std::unique_ptr<Shader> m_Shader[4];
	std::unique_ptr<Engine::FrameBuffer> m_FrameBuffer;
	std::unique_ptr<Engine::FrameBuffer> m_EffectFrameBuffer;
	std::unique_ptr<Engine::CubeMap> m_SkyBox;
	std::unique_ptr<Engine::Model> m_Model;
	glm::vec4 m_ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
	bool m_EffectEnabled = false;
	int m_CurrentEffect = 0;

	int m_Image_Width;
	int m_Image_Height;

};

