#pragma once

#ifdef FOUR_PLATFORM_WINDOWS
	#ifdef FOUR_BUILD_DLL
		#define FOUR_API __declspec(dllexport) 
	#else
		#define FOUR_API __declspec(dllimport)
	#endif
#else
	#error Four only support windows!
#endif
		