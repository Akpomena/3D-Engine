#pragma once

#include "Window.h"

#include "./LayerStack.h"
#include "../Events/ApplicationEvent.h"
#include "../ImGui/ImGuiLayer.h"

namespace Engine {

	class Application
	{
	public:
		Application(const char* name);
		virtual ~Application();

		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* layer);
		void Close();

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_LastFrameTime = 0.0f;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};


	// To be defined in CLENT
	Application* createApplication();
}
