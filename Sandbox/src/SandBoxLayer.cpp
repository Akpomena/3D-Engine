#include "SandBoxLayer.h"

#include <imgui.h>
#include <glad/glad.h>

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

	glm::vec2 textures[] = {
		// positions        
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f},

		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 0.0f},

		{ 1.0f, 0.0f},
		{ 1.0f, 1.0f},
		{ 0.0f, 1.0f},
		{ 0.0f, 1.0f},
		{ 0.0f, 0.0f},
		{ 1.0f, 0.0f},

		{0.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 1.0f},

		{0.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 1.0f}
	};

	float vertices[] = {
		  // normals           // texture coords
		  0.0f,  0.0f, -1.0f,  
		  0.0f,  0.0f, -1.0f,  
		  0.0f,  0.0f, -1.0f,  
		  0.0f,  0.0f, -1.0f,  
		  0.0f,  0.0f, -1.0f,  
		  0.0f,  0.0f, -1.0f,  

		  0.0f,  0.0f, 1.0f,   
		  0.0f,  0.0f, 1.0f,   
		  0.0f,  0.0f, 1.0f,   
		  0.0f,  0.0f, 1.0f,   
		  0.0f,  0.0f, 1.0f,   
		  0.0f,  0.0f, 1.0f,   

		 -1.0f,  0.0f,  0.0f,  
		 -1.0f,  0.0f,  0.0f,  
		 -1.0f,  0.0f,  0.0f,  
		 -1.0f,  0.0f,  0.0f,  
		 -1.0f,  0.0f,  0.0f,  
		 -1.0f,  0.0f,  0.0f,  

		  1.0f,  0.0f,  0.0f,  
		  1.0f,  0.0f,  0.0f,  
		  1.0f,  0.0f,  0.0f,  
		  1.0f,  0.0f,  0.0f,  
		  1.0f,  0.0f,  0.0f,  
		  1.0f,  0.0f,  0.0f,  

		  0.0f, -1.0f,  0.0f,  
		  0.0f, -1.0f,  0.0f,  
		  0.0f, -1.0f,  0.0f,  
		  0.0f, -1.0f,  0.0f,  
		  0.0f, -1.0f,  0.0f,  
		  0.0f, -1.0f,  0.0f,  

		  0.0f,  1.0f,  0.0f,  
		  0.0f,  1.0f,  0.0f,  
		  0.0f,  1.0f,  0.0f,  
		  0.0f,  1.0f,  0.0f,  
		  0.0f,  1.0f,  0.0f,  
		  0.0f,  1.0f,  0.0f,  
	};

	std::vector<Vertex> Vertices;

	for (int i = 0; i < 36; i++)
	{
		Vertex v;
		v.Position = positions[i];
		v.TexCoords = textures[i];
		Vertices.push_back(v);
	}

	Texture boxTex("assets/textures/box.png", 0, "texture_diffuse");
	std::vector<Texture> tex;
	tex.push_back(boxTex);

	m_Mesh.push_back(std::make_unique<Mesh>(Vertices, tex));
	m_Mesh.push_back(std::make_unique<Mesh>(Vertices, tex));

	glm::vec3 planePositions[] = {
		// positions         
		{ 5.0f, -0.5f,  5.0f},
		{-5.0f, -0.5f,  5.0f},
		{-5.0f, -0.5f, -5.0f},
		
		{ 5.0f, -0.5f,  5.0f},
		{-5.0f, -0.5f, -5.0f},
		{ 5.0f, -0.5f, -5.0f}
	};

	glm::vec2 planeTextures[] = {
		// texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		{2.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 2.0f},
	
		{2.0f, 0.0f},
		{0.0f, 2.0f},
		{2.0f, 2.0f}
	};

	Vertices.clear();

	for (int i = 0; i < 6; i++)
	{
		Vertex v;
		v.Position = planePositions[i];
		v.TexCoords = planeTextures[i];
		Vertices.push_back(v);
	}

	Texture floorTex("assets/textures/marble.png", 0, "texture_diffuse");
	tex.clear();
	tex.push_back(floorTex);

	m_Mesh.push_back(std::make_unique<Mesh>(Vertices, tex));

	m_Mesh[0]->SetPosition({ -1.0f, 0.0f, -1.0f });
	m_Mesh[1]->SetPosition({ 2.0f, 0.0f, 0.0f });

	m_Shader[0] = std::make_unique<Shader>("assets/shaders/BasicVertexShader.vert", "assets/shaders/BasicFragShader.frag");
	m_Shader[1] = std::make_unique<Shader>("assets/shaders/BasicVertexShader.vert", "assets/shaders/SolidColor.frag");
}

void SandBoxLayer::OnDetach()
{
}

void SandBoxLayer::OnUpdate(float ts)
{
	// Camera Controls
	if (Engine::Input::IsKeyPressed(KEY_W))
		m_Camera->ProcessKeyboard(FORWARD, ts);
	if (Engine::Input::IsKeyPressed(KEY_S))
		m_Camera->ProcessKeyboard(BACKWARD, ts);
	if (Engine::Input::IsKeyPressed(KEY_A))
		m_Camera->ProcessKeyboard(LEFT, ts);
	if (Engine::Input::IsKeyPressed(KEY_D))
		m_Camera->ProcessKeyboard(RIGHT, ts);

	// Rendering
	glEnable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	Engine::Renderer::SetClearColor(m_ClearColor);
	Engine::Renderer::Clear();

	Engine::Renderer::BeginScene(*m_Camera, *m_Shader[0]);

	glStencilMask(0x00);
	m_Shader[0]->Bind();
	
	Engine::Renderer::Draw(*m_Mesh[2]);

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);


	m_Mesh[0]->SetScale({ 1.0f, 1.0f, 1.0f });
	m_Mesh[1]->SetScale({ 1.0f, 1.0f, 1.0f });

	Engine::Renderer::Draw(*m_Mesh[0]);
	Engine::Renderer::Draw(*m_Mesh[1]);

	
	Engine::Renderer::BeginScene(*m_Camera, *m_Shader[1]);

	glStencilMask(0x00);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glDisable(GL_DEPTH_TEST);

	m_Shader[1]->Bind();

	m_Mesh[0]->SetScale({ 1.2f, 1.2f, 1.2f });
	m_Mesh[1]->SetScale({ 1.2f, 1.2f, 1.2f });

	Engine::Renderer::Draw(*m_Mesh[0]);
	Engine::Renderer::Draw(*m_Mesh[1]);

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glEnable(GL_DEPTH_TEST);

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
