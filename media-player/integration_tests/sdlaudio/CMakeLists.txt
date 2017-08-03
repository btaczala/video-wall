
mars_add_test(sdlaudio)
target_link_libraries(sdlaudio_tests mars-audio)
target_compile_definitions(sdlaudio_tests PRIVATE TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_data")
set_tests_properties(*/SDLAudioTests.file_exists/* PROPERTIES LABELS "LONG")
