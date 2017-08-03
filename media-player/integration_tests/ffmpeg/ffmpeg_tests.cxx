#include <boost/filesystem.hpp>
#include <fstream>
#include <gtest/gtest.h>

#include "log.hpp"
#include "video/ffmpegrenderer.h"

struct FFMPEGRendererTest_it : public ::testing::Test {
    mars::rendering::FFMPEGBackend backend;
};

TEST_F(FFMPEGRendererTest_it, file_does_not_exists)
{
    EXPECT_ANY_THROW(backend.createVideo("/tmp/this_should_not_exists.avi"));
}

TEST_F(FFMPEGRendererTest_it, file_is_not_a_file) { EXPECT_ANY_THROW(backend.createVideo("/home")); }

//TEST_F(FFMPEGRendererTest_it, valid_file)
//{
    //const std::string data_dir = std::string{ TEST_DIR } + "/test_data/bigbuckbunny_480x272.h265";
    //auto renderer = backend.createVideo(data_dir);

    //std::this_thread::sleep_for(std::chrono::milliseconds(40));
    //ASSERT_TRUE(renderer);
    //EXPECT_EQ(renderer->info().width, 480);
    //EXPECT_EQ(renderer->info().height, 272);

    //auto frame = renderer->frame();

    //ASSERT_TRUE(frame);
    //EXPECT_NE(frame->planes[0].pixels, nullptr);
    //EXPECT_EQ(frame->planes[0].linesize, 480);
    //EXPECT_NE(frame->planes[1].pixels, nullptr);
    //EXPECT_EQ(frame->planes[1].linesize, 240);
    //EXPECT_NE(frame->planes[2].pixels, nullptr);
    //EXPECT_EQ(frame->planes[2].linesize, 240);

    //// eat all frames
    //while (renderer->frame())
        //;

    //EXPECT_FALSE(renderer->frame());
//}

TEST_F(FFMPEGRendererTest_it, one_frame)
{
    const std::string data_dir = std::string{ TEST_DIR } + "/test_data/bigbuckbunny_480x272.h265";
    auto renderer = backend.createVideo(data_dir);

    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    ASSERT_TRUE(renderer);
    EXPECT_EQ(renderer->info().width, 480);
    EXPECT_EQ(renderer->info().height, 272);

    auto frame = renderer->frame();

    ASSERT_TRUE(frame);
    EXPECT_NE(frame->planes[0].pixels, nullptr);
    EXPECT_EQ(frame->planes[0].linesize, 480);
    EXPECT_NE(frame->planes[1].pixels, nullptr);
    EXPECT_EQ(frame->planes[1].linesize, 240);
    EXPECT_NE(frame->planes[2].pixels, nullptr);
    EXPECT_EQ(frame->planes[2].linesize, 240);
}

TEST_F(FFMPEGRendererTest_it, invalid_file)
{
    std::ofstream myFile;
    myFile.open("data2.bin", std::ios::out | std::ios::binary);
    myFile << 0x10;
    myFile.close();
    const std::string data_dir = "data2.bin";
    EXPECT_ANY_THROW(mars::rendering::FFMPEGRenderer renderer{ data_dir });
    boost::filesystem::remove("data2.bin");
}
