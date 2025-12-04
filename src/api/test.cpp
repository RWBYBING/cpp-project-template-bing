#include <api/test.h>

#include <infra/logger.h>

using namespace api::test;

void api::test::LogFromBackend()
{
    LOG_INFO("Log from Backend!");
}