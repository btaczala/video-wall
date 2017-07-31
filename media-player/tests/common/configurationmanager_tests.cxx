#include <gtest/gtest.h>

#include "xmlconfiguration.h"

TEST(ConfigurationManager_ut, file_does_not_exists)
{
    EXPECT_THROW(mars::common::XmlConfigurationManager{ "file_does_not_exists" }, std::runtime_error);
}
