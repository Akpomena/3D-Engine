
#include "Application.h"
#include "../Renderer/Renderer.h"

#include "../Events/KeyEvent.h"
#include <GLFW/glfw3.h>

#include "../Debug/Instrumentor.h"

#include <assert.h>

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const char* name)
	{
		PROFILE_FUNCTION();
		assert(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::make_unique<Window>(WindowProps(name));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlayer(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		PROFILE_FUNCTION();
		while (m_Running)
		{
			double time = glfwGetTime();
			double timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.GetHandled())
				break;
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlayer(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Close()
	{
		m_Running = false;
		m_Window->ShutDown();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Close();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
			m_Minimized = true;
		else
			m_Minimized = false;

		/*Renderer::WindowResize(e.GetWidth(), e.GetHeight());*/

		return false;
	}

}
