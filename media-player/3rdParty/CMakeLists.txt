
set(SPDLOG_BUILD_TESTING CACHE FORCE OFF)
add_subdirectory(spdlog)

if (BUILD_UNIT_TESTS)
    add_subdirectory(googletest/googletest)
endif()

add_subdirectory(libSDL2pp.git)
