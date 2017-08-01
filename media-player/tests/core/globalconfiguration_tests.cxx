
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>

#include "globalconfiguration.h"

TEST(GlobalConfigurationTests_ut, fontPaths)
{
    mars::core::ConfigurationManager cfg;
    const std::string homeFontsPath
        = (boost::filesystem::path{ std::getenv("HOME") } / ".config" / "mars" / "fonts").string();
    std::vector<std::string> expectedFontPaths{ "/usr/share/fonts", "/opt/mars/fonts", homeFontsPath };
    EXPECT_EQ(cfg.fontPaths(), expectedFontPaths);
}

TEST(GlobalConfigurationTests_ut, uuid)
{
    mars::core::ConfigurationManager cfg;

    EXPECT_EQ(cfg.uuid(), "%UUID%");
}
