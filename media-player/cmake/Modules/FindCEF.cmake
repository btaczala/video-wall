#Copyright(c) 2016 The Chromium Embedded Framework Authors.All rights
#reserved.Use of this source code is governed by a BSD - style license that
#can be found in the LICENSE file.

#
#This file is the CEF CMake configuration entry point and should be loaded
#using `find_package(CEF REQUIRED)`.See the top - level CMakeLists.txt file
#included with the CEF binary distribution for usage information.
#

#Find the CEF binary distribution root directory.
set(_CEF_ROOT "") if (CEF_ROOT AND IS_DIRECTORY "${CEF_ROOT}") set(_CEF_ROOT "${CEF_ROOT}")
    set(_CEF_ROOT_EXPLICIT 1) else() set(_ENV_CEF_ROOT "") if (DEFINED ENV{ CEF_ROOT }) file(
        TO_CMAKE_PATH "$ENV{CEF_ROOT}" _ENV_CEF_ROOT) endif() if (_ENV_CEF_ROOT AND IS_DIRECTORY "${_ENV_CEF_ROOT}")
        set(_CEF_ROOT "${_ENV_CEF_ROOT}") set(_CEF_ROOT_EXPLICIT 1) endif() unset(_ENV_CEF_ROOT) endif()

            if (NOT DEFINED _CEF_ROOT_EXPLICIT)
                message(FATAL_ERROR "Must specify a CEF_ROOT value via CMake or environment variable.") endif()

                    if (NOT IS_DIRECTORY "${_CEF_ROOT}/cmake") message(
                        FATAL_ERROR "No CMake bootstrap found for CEF binary distribution at: ${CEF_ROOT}.") endif()

#Execute additional cmake files from the CEF binary distribution.
                        set(CMAKE_MODULE_PATH $ { CMAKE_MODULE_PATH } "${_CEF_ROOT}/cmake") include("cef_variables")
                            include("cef_macros")

                                set(CEF_INCLUDE_DIRS "${CEF_ROOT}/include;${CEF_ROOT}")

                                    find_library(CEF_DLL_WRAPPER_LIBRARY cef_dll_wrapper PATHS ${ CEF_ROOT } / build
                                        / libcef_dll_wrapper)

                                        find_library(CEF_LIBRARY cef PATHS ${ CEF_ROOT } / ${ CMAKE_BUILD_TYPE })

                                            SET(CEF_LIBRARIES ${ CEF_DLL_WRAPPER_LIBRARY } ${ CEF_LIBRARY })

                                                include(FindPackageHandleStandardArgs)
                                                    mark_as_advanced(CEF_INCLUDE_DIRS CEF_LIBRARIES)

                                                        message(STATUS "CEF libraries = ${CEF_LIBRARIES}")
                                                            message(STATUS "CEF include dirs = ${CEF_INCLUDE_DIRS}")
