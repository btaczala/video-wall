add_executable(FFMPEGTests ffmpeg_tests.cxx)
target_link_libraries(FFMPEGTests gtest gtest_main mars-widgets test_helpers)
target_compile_definitions(FFMPEGTests PRIVATE TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
gtest_add_tests(FFMPEGTests "" ffmpeg_tests.cxx)
