
set(MARS_RENDERER_IMPL "sdl")

add_subdirectory(${MARS_RENDERER_IMPL})
add_library(mars-rendering INTERFACE)

target_include_directories(mars-rendering 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/${MARS_RENDERER_IMPL}
)

target_link_libraries(mars-rendering 
    INTERFACE
    mars-rendering-${MARS_RENDERER_IMPL}
)

