find_package(CEF REQUIRED)
add_library(mars-ui cefrenderhandler.cxx 
    cefbrowserclient.cxx
    widgets/videowidget.cxx
)
target_link_libraries(mars-ui
    ${CEF_LIBRARIES} 
    mars-rendering 
    mars-common
)
target_include_directories(mars-ui PUBLIC ${CEF_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
