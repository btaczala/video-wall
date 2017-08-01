
set(SDL2PP_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/3rdParty/libSDL2pp.git/ ${CMAKE_BINARY_DIR}/3rdParty/libSDL2pp.git/)

add_executable(ffmpeg-sdl-client ffmpeg-sdl-client.cxx)
target_link_libraries(ffmpeg-sdl-client mars-widgets mars-rendering mars-common)
target_include_directories(ffmpeg-sdl-client PUBLIC ${SDL2_INCLUDE_DIR})
target_compile_definitions(ffmpeg-sdl-client PRIVATE TEST_DIR="${CMAKE_SOURCE_DIR}/tests/rendering/test_data")
