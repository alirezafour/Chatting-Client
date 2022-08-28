#pragma once

#include "fourpch.h"
#include "Four/Core.h"
#include "Four/KeyCodes.h"

namespace four {

	class FOUR_API Input 
	{
	public:
		inline static bool IsKeyPressed(Key keycode) { return s_Instance->IsKeyPressedImplementation(keycode); }

		// mouse
		inline static bool ISMouseButtonPressed(MouseKey button) { return s_Instance->IsMouseButtonPressedImplementation(button); }
		inline static std::pair<float, float> GetMouseXY() { return s_Instance->GetMouseXYImplementation(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImplementation(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImplementation(); }

	protected:
		virtual bool IsKeyPressedImplementation(Key keycode) = 0;
		virtual bool IsMouseButtonPressedImplementation(MouseKey button) = 0;
		virtual std::pair<float, float> GetMouseXYImplementation() const = 0;
		virtual float GetMouseXImplementation() const = 0;
		virtual float GetMouseYImplementation() const = 0;

	private:
		static Input* s_Instance;
	};
}