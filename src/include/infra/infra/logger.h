/**
 * @file logger.h
 * @author bing
 * @brief a global, thread-safe logger
 * @version 0.1
 * @date 2025-12-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <memory>
#include <functional>
#include <mutex>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace Infra
{
    using GuiLogCallback = std::function<void(const std::string&)>;

    /**
     * @brief logger based on spdlog
     * 
     * @details 
     *  support the following features:
     *      1. Singleton
     *      2. Thread-safe
     *      3. Support console output and file output
     *      4. Support output to GUI via callback
     * 
     */
    class Logger
    {
    public:
        /**
         * @brief Get the singleton instance
         * 
         * @return Logger& instance
         */
        static Logger& Instance();

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        /**
         * @brief Initialize the logging system
         * 
         * @param logger_name the name of the logger
         * @param log_file_path logging path
         * @param enable_console enable console output
         * @param enable_file enable file output
         * @param max_file_size the maximum size of single file
         * @param max_files the maximum file nums
         */
        void Init(const std::string& logger_name, 
                const std::string& log_file_path,
                bool enable_console, 
                bool enable_file, 
                std::size_t max_file_size = 10 * 1024 * 1024,
                std::size_t max_files = 5);

        /**
         * @brief Set the Level of the logging system
         * 
         * @param level 
         */
        void SetLevel(spdlog::level::level_enum level);

        /**
         * @brief Set the Gui Callback object, for printing log info in the gui
         * 
         * @param cb 
         */
        void SetGuiCallback(GuiLogCallback cb);

        /**
         * @brief Get the Native Logger object, for advanced usage
         * 
         * @return std::shared_ptr<spdlog::logger> the native logger
         */
        std::shared_ptr<spdlog::logger> GetNativeLogger() const;

        /**
         * @brief Logging Interface for api layer
         * 
         * @param level logging level
         * @param text logging content
         */
        void LogText(spdlog::level::level_enum level, std::string_view text);

        /**
         * @brief Logging Interfaces for internal usage
         * 
         */
        template <typename... Args>
        void Trace(fmt::format_string<Args...> fmt, Args&&... args)
        {
            Log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void Debug(fmt::format_string<Args...> fmt, Args&&... args)
        {
            Log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void Info(fmt::format_string<Args...> fmt, Args&&... args)
        {
            Log(spdlog::level::info, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void Warn(fmt::format_string<Args...> fmt, Args&&... args)
        {
            Log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void Error(fmt::format_string<Args...> fmt, Args&&... args)
        {
            Log(spdlog::level::err, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void Critical(fmt::format_string<Args...> fmt, Args&&... args)
        {
            Log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
        }

    private:
        /**
         * @brief internal logging interface: write into spdlog and distribute to the GUI callback
         * 
         */
        template <typename... Args>
        void Log(spdlog::level::level_enum level,
                fmt::format_string<Args...> fmt_str,
                Args&&... args)
        {
            auto logger = logger_;
            if (!logger)
                return;

            logger->log(level, fmt_str, std::forward<Args>(args)...);

            GuiLogCallback cb;
            {
                std::lock_guard<std::mutex> lock(cbMutex_);
                cb = guiCallback_;
            }
            if (cb)
            {
                auto text = fmt::format(fmt_str, std::forward<Args>(args)...);
                cb(text);
            }
        }

    private:
        Logger() = default;
        virtual ~Logger() = default;

        std::shared_ptr<spdlog::logger> logger_;
        GuiLogCallback guiCallback_;
        mutable std::mutex cbMutex_;
    };

    #define LOG_TRACE(...)          ::Infra::Logger::Instance().Trace(__VA_ARGS__)
    #define LOG_DEBUG(...)          ::Infra::Logger::Instance().Debug(__VA_ARGS__)
    #define LOG_INFO(...)           ::Infra::Logger::Instance().Info(__VA_ARGS__)
    #define LOG_WARN(...)           ::Infra::Logger::Instance().Warn(__VA_ARGS__)
    #define LOG_ERROR(...)          ::Infra::Logger::Instance().Error(__VA_ARGS__)
    #define LOG_CRITICAL(...)       ::Infra::Logger::Instance().Critical(__VA_ARGS__)

}