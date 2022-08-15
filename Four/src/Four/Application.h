#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace four {

	class FOUR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// define in clinet
	Application* CreateApplication();

}

