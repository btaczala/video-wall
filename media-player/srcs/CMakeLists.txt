
add_subdirectory(ui)
add_subdirectory(rendering)
add_subdirectory(zones)
add_subdirectory(common)

add_executable(mars main.cxx)
target_link_libraries(mars mars-rendering)
