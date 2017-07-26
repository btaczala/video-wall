add_executable(UITests screenmanager_tests.cxx)
target_link_libraries(UITests gtest gtest_main mars-ui test_helpers)
gtest_add_tests(FFMPEGTests "" screenmanager_tests.cxx)
