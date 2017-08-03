
add_executable(splashscreen splashscreen.cxx)
target_link_libraries(splashscreen mars-widgets mars-rendering-sdl)
target_compile_definitions(splashscreen PRIVATE TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_data")
