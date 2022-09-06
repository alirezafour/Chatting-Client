#include "fourpch.h"
#include "Application.h"

#include "glad/glad.h"

#include "Input.h"

// #temp
#include "glfw/glfw3.h"

#include "Core/Deltatime.h"

namespace four {

#define BIND_FUNC_EVENT(x) std::bind(x, this, std::placeholders::_1)

	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		FOUR_CORE_ASSERT(!m_Instance, "Application already exist.");
		m_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_FUNC_EVENT(&Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}



	Application::~Application()
	{
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNC_EVENT(&Application::OnWindowClose));

		for (auto & it : std::ranges::reverse_view(m_LayerStack))
		{
			if (e.GetHandled())
			{
				break;
			}
			it->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// #temp TODO: platform base
			float time = static_cast<float>(glfwGetTime());

			Deltatime deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			// ImGui ~~~
			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();
			// ImGui ~~~

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}