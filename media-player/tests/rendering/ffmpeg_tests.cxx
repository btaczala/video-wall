#include <gtest/gtest.h>

#include "ffmpegrenderer.h"

TEST(FFMPEGRenderer, simple) {
    mars::rendering::FFMPEGRenderer renderer{
        "/home/bata/Downloads/big_buck_bunny_480p_h264.mov"};
}
