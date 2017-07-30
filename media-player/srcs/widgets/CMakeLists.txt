find_package(CEF REQUIRED)
find_package(FFMPEG REQUIRED)

# see https://trac.ffmpeg.org/ticket/1783
string(REPLACE "/usr/include/" "" FFMPEG_INCLUDE_DIR "${FFMPEG_INCLUDE_DIR}")

add_library(mars-widgets 
    widget.cxx
    html/cefrenderhandler.cxx 
    html/cefbrowserclient.cxx
    html/htmlwidget.cxx
    video/videowidget.cxx
    video/ffmpegrenderer.cxx
    text/textwidget.cxx
)

target_link_libraries(mars-widgets
    ${CEF_LIBRARIES} 
    ${FFMPEG_LIBRARIES}
    mars-rendering 
    mars-common
)
target_include_directories(mars-widgets 
    PUBLIC 
        ${CEF_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${FFMPEG_INCLUDE_DIR}
)
