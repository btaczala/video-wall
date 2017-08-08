find_package(SDL2 REQUIRED)
find_package(LIBVLC)

if(LIBVLC_FOUND)
    add_executable(libvlc-sdl-example main.cxx)
    target_include_directories(libvlc-sdl-example PUBLIC ${SDL2_INCLUDE_DIR} ${LIBVLC_INCLUDE_DIR})
    target_link_libraries(libvlc-sdl-example ${SDL2_LIBRARY} ${LIBVLC_LIBRARY})
endif()
