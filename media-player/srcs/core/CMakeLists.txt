
find_package(Boost REQUIRED COMPONENTS filesystem)
add_library(mars-core
    configuration.cxx
)
target_include_directories(mars-core PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(mars-core ${Boost_LIBRARIES} mars-common)
