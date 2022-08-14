#include <Four.h>

class Sandbox : public four::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};



four::Application* four::CreateApplication()
{
	return new Sandbox();
}