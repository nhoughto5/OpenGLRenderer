#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
class Log {
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

// Core Log Macros
#define OGLR_CORE_ERROR(...)    Log::GetCoreLogger()->error(__VA_ARGS__)
#define OGLR_CORE_WARN(...)     Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OGLR_CORE_INFO(...)     Log::GetCoreLogger()->info(__VA_ARGS__)
#define OGLR_CORE_TRACE(...)    Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OGLR_CORE_FATAL(...)    Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define OGLR_ERROR(...)         Log::GetClientLogger()->error(__VA_ARGS__)
#define OGLR_WARN(...)          Log::GetClientLogger()->warn(__VA_ARGS__)
#define OGLR_INFO(...)          Log::GetClientLogger()->info(__VA_ARGS__)
#define OGLR_TRACE(...)         Log::GetClientLogger()->trace(__VA_ARGS__)
#define OGLR_FATAL(...)         Log::GetClientLogger()->fatal(__VA_ARGS__)