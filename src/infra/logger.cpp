#include <infra/logger.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using namespace Infra;

Logger& Logger::Instance()
{
    static Logger instance;
    return instance;
}

void Logger::Init(const std::string& logger_name, 
                const std::string& log_file_path,
                bool enable_console, 
                bool enable_file, 
                std::size_t max_file_size,
                std::size_t max_files)
{
    std::vector<spdlog::sink_ptr> sinks;

    if (enable_console)
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        sinks.push_back(console_sink);
    }

    if (enable_file)
    {
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            log_file_path, max_file_size, max_files
        );
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        sinks.push_back(file_sink);
    }

    // sinks cannot be empty
    if (sinks.empty())
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        sinks.push_back(console_sink);
    }

    auto logger = std::make_shared<spdlog::logger>(logger_name, sinks.begin(), sinks.end());
    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::warn);

    spdlog::set_default_logger(logger);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    
    logger_ = std::move(logger);
}

void Logger::SetLevel(spdlog::level::level_enum level)
{
    auto logger = logger_;
    if (!logger)
        return;
    logger->set_level(level);
}

void Logger::SetGuiCallback(GuiLogCallback cb)
{
    std::lock_guard<std::mutex> lock(cbMutex_);
    guiCallback_ = std::move(cb);
}

std::shared_ptr<spdlog::logger> Logger::GetNativeLogger() const 
{
    return logger_;
}

void Logger::LogText(spdlog::level::level_enum level, std::string_view text)
{
    auto logger = logger_;
    if (logger)
        logger->log(level, text);
    
    GuiLogCallback cb_copy;
    {
        std::lock_guard<std::mutex> lock(cbMutex_);
        cb_copy = guiCallback_;
    }
    if (cb_copy)
        cb_copy(std::string(text));
}