
set(SPDLOG_BUILD_TESTING CACHE FORCE OFF)
add_subdirectory(spdlog)

if (BUILD_UNIT_TESTS)
    add_subdirectory(googletest/googletest)
    add_subdirectory(trompeloeil)
endif()

add_subdirectory(libSDL2pp.git)
