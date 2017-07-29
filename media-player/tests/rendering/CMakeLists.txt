mars_add_test(ffmpeg)
target_compile_definitions(ffmpeg_tests PRIVATE TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
