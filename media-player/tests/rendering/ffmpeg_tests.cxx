#include <gtest/gtest.h>

#include "ffmpegrenderer.h"
#include "log.hpp"

TEST(FFMPEGRenderer, file_does_not_exists)
{
    EXPECT_ANY_THROW(mars::rendering::FFMPEGRenderer renderer{ "/tmp/this_should_not_exists.avi" });
}

TEST(FFMPEGRenderer, file_is_not_a_file) { EXPECT_ANY_THROW(mars::rendering::FFMPEGRenderer renderer{ "/home" }); }

TEST(FFMPEGRenderer, valid_file)
{
    const std::string data_dir = std::string{ TEST_DIR } + "/test_data/bigbuckbunny_480x272.h265";
    mars::rendering::FFMPEGRenderer renderer{ data_dir };
    auto frame = renderer.frame();

    ASSERT_TRUE(frame);
    EXPECT_NE(frame->planes[0].pixels, nullptr);
    EXPECT_EQ(frame->planes[0].linesize, 480);
    EXPECT_NE(frame->planes[1].pixels, nullptr);
    EXPECT_EQ(frame->planes[1].linesize, 240);
    EXPECT_NE(frame->planes[2].pixels, nullptr);
    EXPECT_EQ(frame->planes[2].linesize, 240);

    auto second = renderer.frame();
    ASSERT_TRUE(second);
    EXPECT_NE(second->planes[0].pixels, nullptr);
    EXPECT_EQ(second->planes[0].linesize, 480);
    EXPECT_NE(second->planes[1].pixels, nullptr);
    EXPECT_EQ(second->planes[1].linesize, 240);
    EXPECT_NE(second->planes[2].pixels, nullptr);
    EXPECT_EQ(second->planes[2].linesize, 240);

}
