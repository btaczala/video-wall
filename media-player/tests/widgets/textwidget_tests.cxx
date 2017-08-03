
#include "configurationmanagermock.hpp"
#include "renderermock.hpp"
#include "systemmanager.h"
#include "text/textwidget.h"
#include <gtest/gtest.h>

TEST(TextWidget_ut, fontname_empty)
{
    RendererMock mock;
    ConfigurationManagerMock cfgMock;
    auto fn = [&]() { mars::widgets::TextWidget w{ "", "", 24, mock, cfgMock }; };
    EXPECT_ANY_THROW(fn());
}

TEST(TextWidget_ut, font_doesnt_exists)
{
    RendererMock mock;
    ConfigurationManagerMock cfgMock;

    std::vector<std::string> paths;
    REQUIRE_CALL(cfgMock, fontsPaths()).RETURN(paths);
    auto fn = [&]() { mars::widgets::TextWidget w{ "arial-black", "black-arial", 24, mock, cfgMock }; };
    EXPECT_ANY_THROW(fn());
}

TEST(TextWidget_ut, font_full_path)
{
    const std::string fontPath = std::string{ TEST_DIR } + "/Hack-Regular.ttf";
    const std::vector<std::string> paths;

    RendererMock mock;
    ConfigurationManagerMock cfgMock;
    auto* fontMock = new FontMock;
    auto* texture = new TextureMock;

    REQUIRE_CALL(cfgMock, fontsPaths()).RETURN(paths);
    REQUIRE_CALL(mock, createFontProxy(fontPath, 24)).RETURN(fontMock);
    REQUIRE_CALL(*fontMock, renderTextProxy("arial-black")).RETURN(texture);
    REQUIRE_CALL(*texture, size()).RETURN(std::make_pair(10, 10));
    auto fn = [&]() { mars::widgets::TextWidget w{ "arial-black", fontPath, 24, mock, cfgMock }; };
    EXPECT_NO_THROW(fn());
}

TEST(TextWidget_ut, proper_font_path_combination)
{
    const std::string fontPath = std::string{ TEST_DIR } + "/Hack-Regular.ttf";
    const std::vector<std::string> paths{ std::string{ TEST_DIR } };

    RendererMock mock;
    ConfigurationManagerMock cfgMock;
    auto* fontMock = new FontMock;
    auto* texture = new TextureMock;

    REQUIRE_CALL(cfgMock, fontsPaths()).RETURN(paths);
    REQUIRE_CALL(mock, createFontProxy(fontPath, 24)).RETURN(fontMock);
    REQUIRE_CALL(*texture, render(0u, 0u));
    REQUIRE_CALL(*texture, size()).RETURN(std::make_pair(10, 10));
    REQUIRE_CALL(*fontMock, renderTextProxy("arial-black")).RETURN(texture);
    auto fn = [&]() {
        mars::widgets::TextWidget w{ "arial-black", "Hack-Regular.ttf", 24, mock, cfgMock };
        w.render();
    };
    EXPECT_NO_THROW(fn());
}
