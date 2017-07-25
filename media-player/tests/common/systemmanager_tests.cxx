#include <gtest/gtest.h>
#include "log.hpp"
#include "systemmanager.h"

std::shared_ptr<spdlog::logger> kDefaultLogger;

TEST(SystemManager, simple) {
    mars::common::SystemManager smgr;
    auto addresses = smgr.getIP();

    auto contains = [](const auto& container, const auto& value) -> bool {

        auto it = std::find_if(
            std::begin(container), std::end(container),
            [&value](const auto& v) -> bool { return v.iface == value; });

        return it != std::end(container);
    };

    EXPECT_NE(addresses.size(), 0u);
    EXPECT_TRUE(contains(addresses, "lo"));
}

int main(int argc, char* argv[]) {
    kDefaultLogger = spdlog::stdout_color_mt("mars");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
