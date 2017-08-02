
set(SPDLOG_BUILD_TESTING CACHE FORCE OFF) add_subdirectory(spdlog)

    if (BUILD_WITH_UNIT_TESTS) add_subdirectory(googletest / googletest) add_subdirectory(trompeloeil) endif()

        add_subdirectory(embed - resource) set(JSON_BuildTests CACHE FORCE OFF) add_subdirectory(json)
