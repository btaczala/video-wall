#include "log.hpp"
#include <cstdlib>
#include <gtest/gtest.h>

extern std::shared_ptr<spdlog::logger> loggerSetup(
    const std::string& name, spdlog::level::level_enum ll = spdlog::level::info);

TEST(Logger, logger_env_variable_set)
{
    char* env = const_cast<char*>("MARS_DEBUG=");
    putenv(env);

    EXPECT_EQ(kDefaultLogger->level(), spdlog::level::info);
    spdlog::drop("mars");
    EXPECT_NO_THROW(kDefaultLogger = loggerSetup("mars"));

    EXPECT_EQ(kDefaultLogger->level(), spdlog::level::debug);
}
