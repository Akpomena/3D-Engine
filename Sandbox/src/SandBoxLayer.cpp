#include "SandBoxLayer.h"

#include <imgui.h>

void SandBoxLayer::OnAttach()
{
	m_Camera = std::make_unique<Camera>(&Engine::Application::Get().GetWindow(), glm::vec3(0.0f, 0.0f, 3.0f));

	glm::vec3 positions[] = {
		// positions        
		{-0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
							 
		{-0.5f, -0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
		{-0.5f, -0.5f,  0.5f},
							 
		{-0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
							 
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
							 
		{-0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{-0.5f, -0.5f,  0.5f},
		{-0.5f, -0.5f, -0.5f},
							 
		{-0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f, -0.5f}
	};

	float vertices[] = {
		  // normals           // texture coords
		  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		 -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	std::vector<Vertex> Vertices;

	for (int i = 0; i < 36; i++)
	{
		Vertex v;
		v.Position = positions[i];
		Vertices.push_back(v);
	}

	m_Mesh = std::make_unique<Mesh>(Vertices);

	m_Shader = std::make_unique<Shader>("assets/shaders/BasicVertexShader.vert", "assets/shaders/BasicFragShader.frag");
}

void SandBoxLayer::OnDetach()
{
}

void SandBoxLayer::OnUpdate(float ts)
{

	if (Engine::Input::IsKeyPressed(KEY_W))
		m_Camera->ProcessKeyboard(FORWARD, ts);
	if (Engine::Input::IsKeyPressed(KEY_S))
		m_Camera->ProcessKeyboard(BACKWARD, ts);
	if (Engine::Input::IsKeyPressed(KEY_A))
		m_Camera->ProcessKeyboard(LEFT, ts);
	if (Engine::Input::IsKeyPressed(KEY_D))
		m_Camera->ProcessKeyboard(RIGHT, ts);

	m_Shader->Bind();

	Engine::Renderer::SetClearColor(m_ClearColor);
	Engine::Renderer::Clear();

	Engine::Renderer::BeginScene(*m_Camera, *m_Shader);

	glm::mat4 model = glm::mat4(1.0f);
	m_Shader->SetUniformMat4("u_Model", model);

	Engine::Renderer::Draw(*m_Mesh);
	//Engine::Renderer::EndScene();
}

float lastX;
float lastY;
bool firstMouse = true;
bool mouseMove = true;


void SandBoxLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent event)
		{
			if (event.GetKeyCode() == KEY_ESCAPE)
				Engine::Application::Get().Close();
		
			if (event.GetKeyCode() == KEY_ENTER)
			{
				firstMouse = true;
				Engine::Application::Get().GetWindow().enableCursor(mouseMove);
				mouseMove = !mouseMove;
			}

			return true;
		});

	dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent event)
		{
			m_Camera->ProcessMouseScroll(static_cast<float>(event.GetYOffset()));
			return true;
		});

	dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent event)
		{
			float xpos = static_cast<float>(event.GetX());
			float ypos = static_cast<float>(event.GetY());

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;

			if (mouseMove)
				m_Camera->ProcessMouseMovement(xoffset, yoffset);

			return true;
		});
}

void SandBoxLayer::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", (float*)&m_ClearColor);
}
