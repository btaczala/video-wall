
#include "renderermock.hpp"
#include "text/textwidget.h"
#include <gtest/gtest.h>

TEST(TextWidget, simple)
{
    RendererMock mock;
    mars::widgets::TextWidget w{ mock, "" };
}
