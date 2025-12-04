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

int main()
{
    api::logging::Config cfg;
    api::logging::Init(cfg);

    return 0;
}