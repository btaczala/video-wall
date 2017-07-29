
add_library(test_helpers logger_helpers.cxx)
target_link_libraries(test_helpers mars-common)

function(mars_add_test name)
    add_executable(${name}_tests ${name}_tests.cxx)
    target_link_libraries(${name}_tests gtest gtest_main mars-widgets test_helpers test-mocks)
    gtest_add_tests(${name}_tests "" ${name}_tests.cxx)
endfunction()

add_subdirectory(mocks)
add_subdirectory(rendering)
add_subdirectory(common)
add_subdirectory(ui)
add_subdirectory(widgets)
