#pragma once

// 日志类

#include <memory.h>
#include "Core.h"
#include "spdlog/spdlog.h""

namespace Pigeon {

	class PIGEON_API Log
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

// Core 日志宏
#define PG_CORE_TRACE(...)	::Pigeon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PG_CORE_INFO(...)	::Pigeon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PG_CORE_WARN(...)	::Pigeon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PG_CORE_ERROR(...)	::Pigeon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PG_CORE_FATAL(...)	::Pigeon::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client 日志宏
#define PG_TRACE(...)	::Pigeon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PG_INFO(...)	::Pigeon::Log::GetClientLogger()->info(__VA_ARGS__)
#define PG_WARN(...)	::Pigeon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PG_ERROR(...)	::Pigeon::Log::GetClientLogger()->error(__VA_ARGS__)
#define PG_FATAL(...)	::Pigeon::Log::GetClientLogger()->fatal(__VA_ARGS__)