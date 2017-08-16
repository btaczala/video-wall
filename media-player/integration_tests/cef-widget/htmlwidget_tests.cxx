#include <gtest/gtest.h>
#include <trompeloeil.hpp>

#include <cef_app.h>

#include "html/htmlwidget.h"
#include "renderermock.hpp"

struct HTMLWidgetTestCEFSetup : public ::testing::Test {
    static void SetUpTestCase()
    {
        std::cout << "Running!" << std::endl;
        CefMainArgs args;
        CefSettings settings;
        settings.no_sandbox = 1;
        CefString(&settings.browser_subprocess_path) = "/home/bata/Projects/mars-linux/mars-linux.git/media-player/"
                                                       "build/tests/widgets/htmlwidget_test_subprocess";
        // settings.browser_subprocess_path = "subprocess";
        CefInitialize(args, settings, nullptr, nullptr);
    }
    static void TearDownTestCase() { CefShutdown(); }
};

TEST_F(HTMLWidgetTestCEFSetup, creation)
{
    using namespace mars::windowing;
    RendererMock rMock;
    Texture* texture = nullptr;
    REQUIRE_CALL(rMock, createTextureProxy(10, 10, mars::windowing::PixelFormat::Unknown)).RETURN(texture);
    mars::widgets::HTMLWidget html{ "", rMock, 10, 10 };

    EXPECT_TRUE(html.update());
}
