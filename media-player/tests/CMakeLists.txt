
add_library(test_helpers logger_helpers.cxx)
target_link_libraries(test_helpers mars-common)

add_subdirectory(rendering)
add_subdirectory(common)
add_subdirectory(ui)
