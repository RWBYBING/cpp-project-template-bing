/**
 * @file log.h
 * @author bing
 * @brief all the functions related to the logging system
 * @version 0.1
 * @date 2025-12-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <string_view>

namespace api
{
    namespace logging
    {
        /**
         * @brief Definition of logging level
         * 
         */
        enum class LogLevel
        {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Critical
        };

        /**
         * @brief Logging Configuration
         * 
         */
        struct Config
        {
            std::string logger_name{"app"};
            std::string log_file_path{"logs/app.log"};
            bool enable_console{true};
            bool enable_file{false};
            std::size_t max_file_size{10*1024*1024};
            std::size_t max_files{5};
        };

        using GuiLogCallback = std::function<void(std::string_view)>;

        /**
         * @brief Initialize the logger component in the backend
         * 
         * @param cfg 
         */
        void Init(const Config& cfg);

        /**
         * @brief Set the Logging Level
         * 
         * @param level logging level
         */
        void SetLevel(LogLevel level);

        /**
         * @brief Set the Gui Callback
         * 
         * @param cb callback
         */
        void SetGuiCallback(GuiLogCallback cb);

        /**
         * @brief Logging with trace level
         * 
         * @param text logging context
         */
        void Trace(std::string_view text);

        /**
         * @brief Logging with debug level
         * 
         * @param text logging context
         */
        void Debug(std::string_view text);

        /**
         * @brief Logging with info level
         * 
         * @param text logging context
         */
        void Info(std::string_view text);
        
        /**
         * @brief Logging with warn level
         * 
         * @param text logging context
         */
        void Warn(std::string_view text);
        
        /**
         * @brief Logging with error level
         * 
         * @param text logging context
         */
        void Error(std::string_view text);
        
        /**
         * @brief Logging with critical level
         * 
         * @param text logging context
         */
        void Critical(std::string_view text);
    }
}

