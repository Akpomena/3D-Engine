#include "SandBoxLayer.h"

#include <imgui.h>
#include <glad/glad.h>
#include <iostream>

std::unique_ptr<VertexArray> quadVAO;

void SandBoxLayer::OnAttach()
{
	m_Camera = std::make_unique<Camera>(&Engine::Application::Get().GetWindow(), glm::vec3(0.0f, 0.0f, 3.0f));

	m_Image_Width = Engine::Application::Get().GetWindow().GetWidth();
	m_Image_Height = Engine::Application::Get().GetWindow().GetHeight();

	glm::vec3 positions[] = {
		// Back Face      
		{ 0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
				
		// Front Face
		{-0.5f, -0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
		{-0.5f, -0.5f,  0.5f},
							
		// Left Face
		{-0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
				
		// Right Face
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f},
							 
		{-0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{-0.5f, -0.5f,  0.5f},
		{-0.5f, -0.5f, -0.5f},
							 
		// Top Face
		{-0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{-0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
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

	std::vector<Engine::Vertex> Vertices;

	for (int i = 0; i < 36; i++)
	{
		Engine::Vertex v;
		v.Position = positions[i];
		v.TexCoords = textures[i];
		Vertices.push_back(v);
	}

	Texture boxTex("assets/textures/box.png", 0, "texture_diffuse");
	std::vector<Texture> tex;
	tex.push_back(boxTex);

	m_Mesh.push_back(std::make_unique<Engine::Mesh>(Vertices, tex));
	m_Mesh.push_back(std::make_unique<Engine::Mesh>(Vertices, tex));

	glm::vec3 planePositions[] = {
		// positions         
		{ 5.0f, -0.5f,  5.0f},
		{-5.0f, -0.5f, -5.0f},
		{-5.0f, -0.5f,  5.0f},
		
		
		{ 5.0f, -0.5f,  5.0f},
		{ 5.0f, -0.5f, -5.0f},
		{-5.0f, -0.5f, -5.0f}
	};

	glm::vec2 planeTextures[] = {
		// texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		{1.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 1.0f},
	
		{1.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 1.0f}
	};

	glm::vec3 vegPositions[] = {
		// positions         
		{ 0.0f,  0.5f, 0.0f},
		{ 0.0f, -0.5f, 0.0f},
		{ 1.0f, -0.5f, 0.0f},
						 
		{ 0.0f,  0.5f, 0.0f},
		{ 1.0f, -0.5f, 0.0f},
		{ 1.0f,  0.5f, 0.0f}
	};

	glm::vec2 vegTextures[] = {
		// texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		{0.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 0.0f},

		{0.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f}
	};

	Vertices.clear();

	for (int i = 0; i < 6; i++)
	{
		Engine::Vertex v;
		v.Position = planePositions[i];
		v.TexCoords = planeTextures[i];
		Vertices.push_back(v);
	}

	Texture floorTex("assets/textures/marble.png", 0, "texture_diffuse");
	tex.clear();
	tex.push_back(floorTex);

	m_Mesh.push_back(std::make_unique<Engine::Mesh>(Vertices, tex));

	m_Mesh[0]->SetPosition({ -1.0f, 0.0f, -1.0f });
	m_Mesh[1]->SetPosition({ 2.0f, 0.0f, 0.0f });

	// Grasses
	Vertices.clear();

	for (int i = 0; i < 6; i++)
	{
		Engine::Vertex v;
		v.Position = vegPositions[i];
		v.TexCoords = vegTextures[i];
		Vertices.push_back(v);
	}

	Texture grassTex("assets/textures/window.png", 0, "texture_diffuse");
	tex.clear();
	tex.push_back(grassTex);

	std::vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	int i = 0;

	for (auto& loc : vegetation)
	{
		m_Windows.push_back(std::make_unique<Engine::Mesh>(Vertices, tex));
		m_Windows[i]->SetPosition(loc);

		i++;
	}

	m_Shader[0] = std::make_unique<Shader>("assets/shaders/BasicVertexShader.vert", "assets/shaders/BasicFragShader.frag");
	m_Shader[1] = std::make_unique<Shader>("assets/shaders/BasicVertexShader.vert", "assets/shaders/SolidColor.frag");
	m_Shader[2] = std::make_unique<Shader>("assets/shaders/ScreenShader.vert", "assets/shaders/ScreenShader.frag");


	float verts[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	quadVAO = std::make_unique<VertexArray>();
	VertexBuffer buf(&verts, sizeof(verts));
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);

	quadVAO->AddBuffer(buf, layout);
	glBindVertexArray(0);


	m_FrameBuffer = std::make_unique<Engine::FrameBuffer>(Engine::FrameBufferProp(m_Image_Width, m_Image_Height, true));
	m_EffectFrameBuffer = std::make_unique<Engine::FrameBuffer>(Engine::FrameBufferProp(m_Image_Width, m_Image_Height, false));
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

	// first pass
	m_FrameBuffer->Bind();

	Engine::Renderer::SetClearColor(m_ClearColor);
	Engine::Renderer::Clear();

	Engine::Renderer::BeginScene(*m_Camera, *m_Shader[0]);

	std::map<float, int> sorted;

	for (int i = 0; i < m_Windows.size(); i++)
	{
		float distance = glm::length(m_Camera->Position - m_Windows[i]->GetPosition());
		sorted[distance] = i;
	}

	for(auto& mesh: m_Mesh)
		Engine::Renderer::Draw(*mesh);

	for (std::map<float, int>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
		Engine::Renderer::Draw(*m_Windows[it->second]);

	//Engine::Renderer::EndScene();
	
	
	// second pass
	m_FrameBuffer->UnBind(); // back to default

	if (m_EffectEnabled)
	{
		m_EffectFrameBuffer->Bind();
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader[2]->Bind();
		quadVAO->bind();
		m_Shader[2]->SetUniformInt("selectedEffect", m_CurrentEffect);
		glBindTexture(GL_TEXTURE_2D, m_FrameBuffer->GetTextureAttachment());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		m_EffectFrameBuffer->UnBind();
	}
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
				Engine::Application::Get().GetWindow().EnableCursor(mouseMove);
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
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

	bool p_open = true;

	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		//ShowDockingDisabledMessage();
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
			ImGui::MenuItem("Padding", NULL, &opt_padding);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();

			if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
				p_open = false;
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::Begin("Side Bar");
	ImGui::ColorEdit4("Clear Color", (float*)&m_ClearColor);
	ImGui::Checkbox("Enable Effect", &m_EffectEnabled);

	if (m_EffectEnabled)
	{
		const char* items[] = { "Inversion", "GrayScale", "Sharpen", "Blur", "Edge Detection" };
		ImGui::Combo("combo", &m_CurrentEffect, items, IM_ARRAYSIZE(items));
	}

	ImGui::End();

	ImGui::Begin("OpenGL Texture Text");

	ImVec2 view = ImGui::GetContentRegionAvail();

	if (view.x != m_Image_Width || view.y != m_Image_Height)
	{
		if (view.x != 0 && view.y != 0)
		{
			m_Image_Width = view.x;
			m_Image_Height = view.y;

			Engine::Application::Get().GetWindow().SetViewPort(view.x, view.y);
			m_FrameBuffer->UpdateBufferSize(view.x, view.y);
			m_EffectFrameBuffer->UpdateBufferSize(view.x, view.y);
		}
	}


	ImGui::Image(m_EffectEnabled ? (void*)m_EffectFrameBuffer->GetTextureAttachment() : (void*)m_FrameBuffer->GetTextureAttachment(), 
		ImVec2(m_Image_Width, m_Image_Height), { 0, 1 }, { 1, 0 });

	ImGui::End();

	ImGui::End();

}
