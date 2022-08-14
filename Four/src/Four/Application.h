#pragma once

#include "Core.h"

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

