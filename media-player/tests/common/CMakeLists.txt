add_executable(SystemManagerTests systemmanager_tests.cxx)
target_link_libraries(SystemManagerTests gtest gtest_main mars-common test_helpers)
gtest_add_tests(SystemManagerTests "" systemmanager_tests.cxx)

add_executable(ScreenManagerTests screenmanager_tests.cxx)
target_link_libraries(ScreenManagerTests gtest gtest_main mars-common test_helpers)
gtest_add_tests(ScreenManagerTests "" screenmanager_tests.cxx)
