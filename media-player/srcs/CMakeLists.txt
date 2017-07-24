
add_subdirectory(ui)
add_subdirectory(rendering)
add_subdirectory(zones)

add_executable(mars main.cxx)
target_link_libraries(mars mars-rendering)
