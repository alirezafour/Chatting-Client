#include <Four.h>

class Sandbox : public four::Application
{
public:
	Sandbox()
	{
		FOUR_LOG_TRACE("Hello World!");
	}
	~Sandbox()
	{

	}
};



four::Application* four::CreateApplication()
{
	return new Sandbox();
}