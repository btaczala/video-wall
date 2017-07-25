find_package(Threads REQUIRED)

add_library(mars-common loggers.cxx systemmanager.cxx)
target_include_directories(mars-common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mars-common spdlog ${CMAKE_THREAD_LIBS_INIT})
