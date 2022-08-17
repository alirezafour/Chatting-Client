#pragma once

#include "fourpch.h"

#include "Four/Core.h"
#include "Four/Event/Event.h"

namespace four {

	struct WindowProperty
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperty(const std::string& title = "Four", uint32_t width = 1280, uint32_t height = 720)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	// Window interface
	class FOUR_API Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		static Window* Create(const WindowProperty& props = WindowProperty());

	};
}