#include <gtest/gtest.h>

#include "ffmpegrenderer.h"
#include "log.hpp"

TEST(FFMPEGRenderer, file_does_not_exists)
{
    EXPECT_ANY_THROW(mars::rendering::FFMPEGRenderer renderer{ "/tmp/this_should_not_exists.avi" });
}

TEST(FFMPEGRenderer, file_is_not_a_file)
{
    EXPECT_ANY_THROW(mars::rendering::FFMPEGRenderer renderer{ "/home"});
}
