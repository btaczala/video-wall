find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(mars-rendering 
    sdlrenderer.cxx 
    sdlhelpers.cxx
    sdlfont.cxx
)
target_include_directories(mars-rendering 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE 
        ${SDL2_INCLUDE_DIRS} 
        ${SDL2_IMAGE_INCLUDE_DIR} 
        ${SDL2_TTF_INCLUDE_DIR} 
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/srcs/
)

target_link_libraries(mars-rendering 
    mars-common
    ${SDL2_TTF_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_LIBRARY} 
    ${Boost_LIBRARIES}
)

