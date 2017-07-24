find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(FFMPEG REQUIRED)

add_library(mars-rendering ffmpegrenderer.cxx)
target_include_directories(mars-rendering PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${FFMPEG_INCLUDE_DIR})
target_link_libraries(mars-rendering 
    ${SDL2_TTF_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_LIBRARIES} 
    ${FFMPEG_avformat_LIBRARY} ${FFMPEG_avcodec_LIBRARY})

