
add_library(test_helpers logger_helpers.cxx)
target_link_libraries(test_helpers mars-common)

function(mars_add_test name)
    add_executable(${name}_tests ${name}_tests.cxx)
    target_link_libraries(${name}_tests gtest gtest_main mars-widgets mars-core mars-rendering test_helpers test-mocks)
    gtest_add_tests(${name}_tests "" ${name}_tests.cxx)
    if(MEMORYCHECK_COMMAND)
        add_custom_target(${name}_tests_valgrind
            COMMAND "${MEMORYCHECK_COMMAND}" ${MEMORYCHECK_COMMAND_OPTIONS} ${CMAKE_CURRENT_BINARY_DIR}/${name}_tests
        )
    endif()
    target_compile_options(${name}_tests PRIVATE -Wno-inconsistent-missing-override)
endfunction()

add_subdirectory(mocks)
add_subdirectory(common)
add_subdirectory(ui)
add_subdirectory(widgets)
add_subdirectory(core)
add_subdirectory(rendering)
