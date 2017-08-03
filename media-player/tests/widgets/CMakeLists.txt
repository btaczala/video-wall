mars_add_test(videowidget)
mars_add_test(textwidget)
mars_add_test(widget)


target_compile_definitions(textwidget_tests PRIVATE TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_data")
