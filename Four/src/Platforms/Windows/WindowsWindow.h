#pragma once

#include "Four/Window.h"

#include <GLFW/glfw3.h>

namespace four {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperty& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return m_Data.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;

	private:
		virtual void Initialize(const WindowProperty& props);

		virtual void UnInitialize();

		void SetWindowSizeCallback();
		void SetKeyCallback();
		void SetMouseButtonCallback();
		void SetScrollCallback();
		void SetCursorPosCallback();
		void SetErrorCallback();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFunction EventCallback;
		};

		WindowData m_Data;
	};

}

