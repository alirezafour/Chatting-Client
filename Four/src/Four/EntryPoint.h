#pragma once

#ifdef FOUR_PLATFORM_WINDOWS

extern four::Application* four::CreateApplication();

int main(int argc, char** argv)
{
	four::Log::Init();
	FOUR_CORE_WARN("Initialized core logger!");
	int a = 5;
	FOUR_INFO("Initialized client logger! var = {0} ", a);

	auto app = four::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif