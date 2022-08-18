#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Window.h"

namespace four {

	class FOUR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	protected:
		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// define in clinet
	Application* CreateApplication();

}

