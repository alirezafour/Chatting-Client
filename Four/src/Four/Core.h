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

#ifdef FOUR_ASSERTS_ENABLE // INFO: break is windows only
	#define FOUR_CORE_ASSERT(x, ...) if(!x){ FOUR_LOG_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}
	#define FOUR_ASSERT(x, ...) if(!x){ FOUR_LOG_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}
#else // FOUR_ASSERTS
	#define FOUR_CORE_ASSERT(x, ...)
	#define FOUR_ASSERT(x, ...)
#endif 

		
#define BIT(x) (1 << x)