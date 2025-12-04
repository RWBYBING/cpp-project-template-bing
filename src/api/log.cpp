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
    Infra::Logger::Instance().Init(
        cfg.logger_name,
        cfg.log_file_path,
        cfg.enable_console,
        cfg.enable_file,
        cfg.max_file_size,
        cfg.max_files
    );
}

void api::logging::SetLevel(LogLevel level)
{
    Infra::Logger::Instance().SetLevel(LogLevel2SpdlogLevel(level));
}

void api::logging::SetGuiCallback(GuiLogCallback cb)
{
    // use std::string in api, use const std::string& in backend
    Infra::Logger::Instance().SetGuiCallback(
        [cb = std::move(cb)](const std::string& text)
        {
            if (cb)
                cb(text);
        }
    );
}

void api::logging::Trace(std::string_view text)
{
    Infra::Logger::Instance().LogText(spdlog::level::trace, text);
}

void api::logging::Debug(std::string_view text)
{
    Infra::Logger::Instance().LogText(spdlog::level::debug, text);
}

void api::logging::Info(std::string_view text)
{
    Infra::Logger::Instance().LogText(spdlog::level::info, text);
}

void api::logging::Warn(std::string_view text)
{
    Infra::Logger::Instance().LogText(spdlog::level::warn, text);
}

void api::logging::Error(std::string_view text)
{
    Infra::Logger::Instance().LogText(spdlog::level::err, text);
}

void api::logging::Critical(std::string_view text)
{
    Infra::Logger::Instance().LogText(spdlog::level::critical, text);
}