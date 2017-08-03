
#include <gtest/gtest.h>

#include "sdlaudio.h"
#include "stopwatch.hpp"
#include <thread>

using namespace mars::audio;

TEST(SDLAudio_it, file_does_not_exists)
{
    SDLAudio player{ "" };

    player.play();

    EXPECT_FALSE(player.playing());
}

struct SDLAudioTests_it : public ::testing::TestWithParam<std::tuple<int, std::string>> {
};

TEST_P(SDLAudioTests_it, file_exists)
{
    const std::string file = std::string{ TEST_DIR } + "/" + std::get<std::string>(GetParam());
    SDLAudio::initialize();

    Stopwatch<std::chrono::seconds> sw;

    SDLAudio player{ file };
    player.play();
    EXPECT_TRUE(player.playing());

    while (player.playing()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    EXPECT_GE(sw.elapsed(), std::get<int>(GetParam()));
    EXPECT_FALSE(player.playing());
}

INSTANTIATE_TEST_CASE_P(Mp3OggFiles, SDLAudioTests_it,
    ::testing::Values(std::make_tuple(2, "DJ-Lazer.mp3"), std::make_tuple(2, "DJ-Lazer.ogg")));
