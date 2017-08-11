
#include "configurationmanagermock.hpp"
#include "renderermock.hpp"
#include "systemmanager.h"
#include "text/textwidget.h"
#include <gtest/gtest.h>

TEST(TextWidget, fontname_empty)
{
    RendererMock mock;
    ConfigurationManagerMock cfgMock;
    auto fn = [&]() { mars::widgets::TextWidget w{ "", "", 24, mock, cfgMock }; };
    EXPECT_ANY_THROW(fn());
}

TEST(TextWidget, font_doesnt_exists)
{
    RendererMock mock;
    ConfigurationManagerMock cfgMock;

    std::vector<std::string> paths;
    REQUIRE_CALL(cfgMock, fontsPaths()).RETURN(paths);
    auto fn = [&]() { mars::widgets::TextWidget w{ "arial-black", "black-arial", 24, mock, cfgMock }; };
    EXPECT_ANY_THROW(fn());
}

TEST(TextWidget, font_full_path)
{
    const std::string fontPath = std::string{ TEST_DIR } + "/Hack-Regular.ttf";
    const std::vector<std::string> paths;

    RendererMock mock;
    ConfigurationManagerMock cfgMock;
    auto* texture = new TextureMock;

    REQUIRE_CALL(cfgMock, fontsPaths()).RETURN(paths);
    REQUIRE_CALL(mock, createTextProxy("arial-black", fontPath, 24)).RETURN(texture);
    REQUIRE_CALL(*texture, size()).RETURN(std::make_pair(10, 10));
    auto fn = [&]() { mars::widgets::TextWidget w{ "arial-black", fontPath, 24, mock, cfgMock }; };
    EXPECT_NO_THROW(fn());
}

TEST(TextWidget, proper_font_path_combination)
{
    const std::string fontPath = std::string{ TEST_DIR } + "/Hack-Regular.ttf";
    const std::vector<std::string> paths{ std::string{ TEST_DIR } };

    RendererMock mock;
    ConfigurationManagerMock cfgMock;
    auto* texture = new TextureMock;

    REQUIRE_CALL(cfgMock, fontsPaths()).RETURN(paths);
    REQUIRE_CALL(mock, createTextProxy("arial-black", fontPath, 24)).RETURN(texture);
    REQUIRE_CALL(*texture, render(0u, 0u));
    REQUIRE_CALL(*texture, size()).RETURN(std::make_pair(10, 10));
    auto fn = [&]() {
        mars::widgets::TextWidget w{ "arial-black", "Hack-Regular.ttf", 24, mock, cfgMock };
        w.render();
    };
    EXPECT_NO_THROW(fn());
}
