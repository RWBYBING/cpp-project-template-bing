/**
 * @file main.cpp (cli)
 * @author bing
 * @brief entrance of the CLI program
 * @version 0.1
 * @date 2025-12-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <api/log.h>
#include <api/test.h>

#include <iostream>

int main()
{
    api::logging::Config cfg;
    api::logging::Init(cfg);
    api::logging::SetLevel(api::logging::LogLevel::Info);

    api::logging::SetGuiCallback(
        [](std::string_view text)
        {
            std::cout << "Callback: " << text << std::endl;
        }
    );

    api::logging::Info("Log from apps!");

    api::test::LogFromBackend();

    return 0;
}