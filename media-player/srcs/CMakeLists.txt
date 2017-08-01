
add_subdirectory(rendering)
add_subdirectory(zones)
add_subdirectory(widgets)
add_subdirectory(common)
add_subdirectory(core)

add_executable(mars main.cxx)
target_link_libraries(mars mars-rendering)
