#include "fourpch.h"
#include "WindowsWindow.h"

#include "glad/glad.h"

#include "Four/Event/ApplicationEvent.h"
#include "Four/Event/KeyEvent.h"
#include "Four/Event/MouseEvent.h"

namespace four {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error_code, const char* description)
	{
		FOUR_LOG_CORE_ERROR("GLFW Error {0}: {1}", error_code, description);
	}

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
			SetErrorCallback();
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int32_t>(m_Data.Width), static_cast<int32_t>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FOUR_CORE_ASSERT(status, "Failded to init glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Setup GLFW Events
		SetWindowSizeCallback();
		SetKeyCallback();
		SetMouseButtonCallback();
		SetScrollCallback();
		SetCursorPosCallback();


	}

	void WindowsWindow::UnInitialize()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetScrollCallback()
	{
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

				MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
				data.EventCallback(event);

			});
	}

	void WindowsWindow::SetMouseButtonCallback()
	{
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}

				default:
					break;
				}
			});
	}

	void WindowsWindow::SetKeyCallback()
	{
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}

				default:
					break;
				}
			});
	}

	void WindowsWindow::SetWindowSizeCallback()
	{
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) // Window Size callback
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) // Window Close callback
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				WindowCloseEvent event;
				data.EventCallback(event);
			});
	}

	void WindowsWindow::SetCursorPosCallback()
	{
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
				data.EventCallback(event);
			});
	}


	void WindowsWindow::SetErrorCallback()
	{
		glfwSetErrorCallback(GLFWErrorCallback);
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
