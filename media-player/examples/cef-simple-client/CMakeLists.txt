
add_executable(cef-simple-client cef-simple.cxx)
target_link_libraries(cef-simple-client mars-ui mars-rendering mars-common)
target_compile_definitions(cef-simple-client PRIVATE HTML_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

file(COPY ${CEF_ROOT}/Resources/icudtl.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef_100_percent.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef_200_percent.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef_extensions.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/devtools_resources.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/locales DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Release/natives_blob.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Release/snapshot_blob.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

