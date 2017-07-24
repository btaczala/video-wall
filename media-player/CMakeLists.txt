project(CXX)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(BUILD_SHARED_LIBS "Build shared instead of static libraries."              ON)

add_subdirectory(3rdParty)

add_subdirectory(srcs)
if(BUILD_UNIT_TESTS)
    enable_testing()
    include(GTEST_ADD_TESTS)
    add_subdirectory(tests)
endif()

