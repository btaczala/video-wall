
add_executable(ffmpeg-sdl-client ffmpeg-sdl-client.cxx)
target_link_libraries(ffmpeg-sdl-client mars-ui mars-rendering mars-common)
target_include_directories(ffmpeg-sdl-client PUBLIC ${SDL2_INCLUDE_DIR})
target_compile_definitions(ffmpeg-sdl-client PRIVATE TEST_DIR="${CMAKE_SOURCE_DIR}/tests/rendering/test_data")
