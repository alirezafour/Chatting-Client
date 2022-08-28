#include <Four.h>

class ExampleLayer : public four::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override
	{
		if (four::Input::IsKeyPressed(four::Key::KEY_TAB))
		{
			FOUR_LOG_INFO("Tab Key Down");
		}
	}

	void OnEvent(four::Event& event) override
	{
		
	}
};

class Sandbox : public four::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new four::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};



four::Application* four::CreateApplication()
{
	return new Sandbox();
}