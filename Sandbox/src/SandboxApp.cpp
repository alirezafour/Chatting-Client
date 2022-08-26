#include <Four.h>

class ExampleLayer : public four::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override
	{
		FOUR_LOG_INFO("ExampleLayer::Update");
	}

	void OnEvent(four::Event& event) override
	{
		FOUR_LOG_TRACE("{0}", event);
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