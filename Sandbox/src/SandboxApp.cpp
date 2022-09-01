#include <Four.h>
#include "ImGui/imgui.h"

class ExampleLayer : public four::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate(four::Deltatime deltaTime) override
	{
		if (four::Input::IsKeyPressed(four::Key::KEY_TAB))
		{
			FOUR_LOG_INFO("Tab Key Down");
		}
		FOUR_LOG_TRACE("delta time: {0}s ({1}ms).", deltaTime.GetSecond(), deltaTime.GetMilliseconds());
	}

	void OnEvent(four::Event& event) override
	{
		
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("test");
		ImGui::Text("Hello Sandbox!");
		ImGui::End();

	}
};

class Sandbox : public four::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};



four::Application* four::CreateApplication()
{
	return new Sandbox();
}