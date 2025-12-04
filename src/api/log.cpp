#include <api/log.h>

#include <iostream>

#include <infra/logger.h>
#include <spdlog/spdlog.h>

using namespace api::logging;

static spdlog::level::level_enum LogLevel2SpdlogLevel(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Trace:               return spdlog::level::trace;
    case LogLevel::Debug:               return spdlog::level::debug;
    case LogLevel::Info:                return spdlog::level::info;
    case LogLevel::Warn:                return spdlog::level::warn;
    case LogLevel::Error:               return spdlog::level::err;
    case LogLevel::Critical:            return spdlog::level::critical;

    default:
        break;
    }

    return spdlog::level::info;
}

void api::logging::Init(const Config& cfg)
{
    std::cout << 123 << std::endl;
}

