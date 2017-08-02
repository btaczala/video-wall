
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(mars-audio sdlaudio.cxx)
target_include_directories(mars-audio 
    PRIVATE 
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(mars-audio ${SDL2_MIXER_LIBRARIES} mars-common ${SDL2_LIBRARY})

