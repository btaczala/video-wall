# valgrind support

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

if(MEMORYCHECK_COMMAND)
    add_custom_target(valgrind
        COMMAND "${MEMORYCHECK_COMMAND}" --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 ctest)
else()
    message(STATUS "Valgrind was not found")
endif()
