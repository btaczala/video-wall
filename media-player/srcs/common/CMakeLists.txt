find_package(Threads REQUIRED)
find_package(Xrandr REQUIRED)
find_package(XCB REQUIRED)

add_library(mars-common loggers.cxx systemmanager.cxx screenmanager.cxx)
target_include_directories(mars-common 
    PUBLIC 
        ${XRANDR_INCLUDE_DIRS} 
        ${XCB_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(mars-common 
    spdlog
    ${CMAKE_THREAD_LIBS_INIT}
    ${XRANDR_LIBRARIES} 
    ${XCB_LIBRARIES}
)
