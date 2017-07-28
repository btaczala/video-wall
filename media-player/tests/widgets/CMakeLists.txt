add_executable(VideoWidgetTests videowidget_tests.cxx)
target_link_libraries(VideoWidgetTests
    gtest
    gtest_main
    mars-widgets
    test_helpers
    test-mocks
)
gtest_add_tests(VideoWidgetTests "" videowidget_tests.cxx)
