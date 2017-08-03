#include <gtest/gtest.h>

#include "screenmanager.h"

TEST(ScreenManager_it, availableScreens)
{
    mars::common::ScreenManager screenmgr;

    auto screens = screenmgr.availableScreens();

    auto nonEmptyScreen = [](const auto& container) -> bool {

        const auto it = std::find_if(std::begin(container), std::end(container),
            [](const auto& v) -> bool { return v.width != 0 && v.height != 0; });
        return it != std::end(container);
    };

    EXPECT_NE(screens.size(), 0u);

    // at least on screen with some resolution
    EXPECT_TRUE(nonEmptyScreen(screens));
}
