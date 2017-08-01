
find_package(Boost REQUIRED COMPONENTS filesystem)
embed_resources(default_json json/default_config.json)

add_library(mars-core
    globalconfiguration.cxx
    ${default_json}
)

target_include_directories(mars-core 
    PRIVATE 
        ${Boost_INCLUDE_DIRS} 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(mars-core ${Boost_LIBRARIES} mars-common json)

