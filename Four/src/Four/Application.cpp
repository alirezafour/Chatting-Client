#include "fourpch.h"
#include "Application.h"

#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace four {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		FOUR_LOG_TRACE(e);
		while (true);
	}

}