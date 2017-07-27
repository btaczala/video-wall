#include <gtest/gtest.h>

#include "configurationmanager.h"

TEST(ConfigurationManager, file_does_not_exists)
{
    EXPECT_THROW(mars::common::ConfigurationManager{ "file_does_not_exists" }, std::runtime_error);
}
