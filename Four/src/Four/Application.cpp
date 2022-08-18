#include "fourpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"

namespace four {

#define BIND_FUNC_EVENT(x) std::bind(x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_FUNC_EVENT(&Application::OnEvent));
	}

	Application::~Application()
	{

	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNC_EVENT(&Application::OnWindowClose));

		FOUR_LOG_TRACE("{0}", e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}