add_library(test-mocks INTERFACE)
target_include_directories(test-mocks
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/3rdParty/trompeloeil/include
)

