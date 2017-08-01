
set(SDL2PP_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/3rdParty/libSDL2pp.git/ ${CMAKE_BINARY_DIR}/3rdParty/libSDL2pp.git/)

add_executable(video-html-client video-html-client.cxx)
target_link_libraries(video-html-client mars-widgets mars-rendering mars-common)
target_include_directories(video-html-client PUBLIC ${SDL2_INCLUDE_DIR})

file(COPY ${CEF_ROOT}/Resources/icudtl.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef_100_percent.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef_200_percent.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/cef_extensions.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/devtools_resources.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Resources/locales DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Release/natives_blob.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CEF_ROOT}/Release/snapshot_blob.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

