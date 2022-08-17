#pragma once
#include "fourpch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace four {

	class FOUR_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define FOUR_LOG_CORE_TRACE(...)    ::four::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FOUR_LOG_CORE_INFO(...)     ::four::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FOUR_LOG_CORE_WARN(...)     ::four::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FOUR_LOG_CORE_ERROR(...)    ::four::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FOUR_LOG_CORE_FATAL(...)    ::four::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define FOUR_LOG_TRACE(...)         ::four::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FOUR_LOG_INFO(...)          ::four::Log::GetClientLogger()->info(__VA_ARGS__)
#define FOUR_LOG_WARN(...)          ::four::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FOUR_LOG_ERROR(...)         ::four::Log::GetClientLogger()->error(__VA_ARGS__)
#define FOUR_LOG_FATAL(...)         ::four::Log::GetClientLogger()->fatal(__VA_ARGS__)

