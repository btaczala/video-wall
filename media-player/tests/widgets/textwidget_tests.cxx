
#include "renderermock.hpp"
#include "text/textwidget.h"
#include <gtest/gtest.h>

TEST(TextWidget_ut, fontname_empty)
{
    RendererMock mock;
    auto fn = [&mock]() { mars::widgets::TextWidget w{ mock, "", "", 24 }; };
    EXPECT_ANY_THROW(fn());
}

TEST(TextWidget_ut, font_doesnt_exists)
{
    RendererMock mock;

    auto fn = [&mock]() { mars::widgets::TextWidget w{ mock, "arial-black", "black-arial", 24 }; };
    EXPECT_ANY_THROW(fn());
}
