#include <gtest/gtest.h>

#include "screenmanager.h"

TEST(ScreenManager, availableScreens)
{
    mars::ui::ScreenManager screenmgr;

    screenmgr.availableScreens();
}
