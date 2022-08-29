#include "fourpch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "Four/Application.h"

namespace four {

	Input* Input::s_Instance = new WindowInput();

	bool WindowInput::IsKeyPressedImplementation(Key keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));

		return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
	}

	bool WindowInput::IsMouseButtonPressedImplementation(MouseKey button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

		return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
	}

	std::pair<float, float> WindowInput::GetMouseXYImplementation() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		
		return { static_cast<float>(xpos), static_cast<float>(ypos) };
	}

	float WindowInput::GetMouseXImplementation() const
	{
		auto [mouseX, mouseY] = GetMouseXYImplementation();
		return mouseX;
	}

	float WindowInput::GetMouseYImplementation() const
	{
		auto [mouseX, mouseY] = GetMouseXYImplementation();
		return mouseY;
	}

}