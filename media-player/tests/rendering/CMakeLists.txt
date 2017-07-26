add_executable(FFMPEGTests ffmpeg_tests.cxx)
target_link_libraries(FFMPEGTests gtest gtest_main mars-rendering test_helpers)
gtest_add_tests(FFMPEGTests "" ffmpeg_tests.cxx)
