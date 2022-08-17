#include "fourpch.h"
#include "WindowsWindow.h"
#include "Four/Log.h"

namespace four {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperty& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperty& props)
	{
		Initialize(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		UnInitialize();
	}

	void WindowsWindow::Initialize(const WindowProperty& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		FOUR_LOG_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int32_t success = glfwInit();
			FOUR_ASSERT(success, "Count't Initialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int32_t>(m_Data.Width), static_cast<int32_t>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::UnInitialize()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const
	{
		return m_Data.VSync;
	}


}
