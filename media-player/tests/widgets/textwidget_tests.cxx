
#include "renderermock.hpp"
#include "text/textwidget.h"
#include <gtest/gtest.h>

TEST(TextWidget_ut, simple)
{
    auto* fontMock = new FontMock;
    RendererMock mock;

    REQUIRE_CALL(mock, createFontProxy("", 10)).RETURN(fontMock);
    REQUIRE_CALL(*fontMock, renderTextProxy("")).RETURN(nullptr);
    mars::widgets::TextWidget w{ mock, "", "" };
}
