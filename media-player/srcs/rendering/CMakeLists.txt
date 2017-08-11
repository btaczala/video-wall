
set(MARS_RENDERER_IMPL "sdl")

add_subdirectory(${MARS_RENDERER_IMPL})
add_library(mars-rendering STATIC
    renderer.cxx
)

target_include_directories(mars-rendering 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/${MARS_RENDERER_IMPL}
)

target_link_libraries(mars-rendering 
    mars-rendering-${MARS_RENDERER_IMPL}
    mars-widgets
)

