find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(Boost REQUIRED COMPONENTS filesystem)

find_package(FFMPEG REQUIRED)

# see https://trac.ffmpeg.org/ticket/1783
string(REPLACE "/usr/include/" "" FFMPEG_INCLUDE_DIR "${FFMPEG_INCLUDE_DIR}")

add_library(mars-rendering ffmpegrenderer.cxx sdlrenderer.cxx)
target_include_directories(mars-rendering 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE 
        ${FFMPEG_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIRS} 
        ${SDL2_IMAGE_INCLUDE_DIR} 
        ${SDL2_TTF_INCLUDE_DIR} 
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(mars-rendering 
    mars-common
    ${SDL2_TTF_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_LIBRARY} 
    ${FFMPEG_LIBRARIES}
    ${Boost_LIBRARIES}
)

