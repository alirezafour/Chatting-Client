#pragma once
#include "fourpch.h"
#include "Core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"

namespace four {

	class FOUR_API Application
	{
	public:
		Application();
		virtual ~Application();
		inline static Application& Get() { return *m_Instance; }

		void Run();
		inline Window& GetWindow() const { return *m_Window; }

	protected:
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);


	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* m_Instance;
	};

	// define in clinet
	Application* CreateApplication();

}

