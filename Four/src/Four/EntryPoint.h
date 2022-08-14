#pragma once

#ifdef FOUR_PLATFORM_WINDOWS

extern four::Application* four::CreateApplication();

int main(int argc, char** argv)
{
	auto app = four::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif