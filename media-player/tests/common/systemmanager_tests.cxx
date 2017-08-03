#include "configurationmanagermock.hpp"
#include "log.hpp"
#include "systemmanager.h"
#include <gtest/gtest.h>

TEST(SystemManager, simple)
{
    ConfigurationManagerMock cfgMock;
    mars::core::SystemManager smgr{ cfgMock };
    auto addresses = smgr.getIP();

    auto contains = [](const auto& container, const auto& value) -> bool {

        auto it = std::find_if(
            std::begin(container), std::end(container), [&value](const auto& v) -> bool { return v.iface == value; });

        return it != std::end(container);
    };

    EXPECT_NE(addresses.size(), 0u);
    EXPECT_TRUE(contains(addresses, "lo"));
}
