# valgrind support

find_program( MEMORYCHECK_COMMAND valgrind )
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes" "--leak-check=full" "--tool=memcheck" "--leak-check=yes" "--show-reachable=yes" "--num-callers=20")

if(MEMORYCHECK_COMMAND)
    add_custom_target(valgrind
        COMMAND "${MEMORYCHECK_COMMAND}" ${MEMORYCHECK_COMMAND_OPTIONS} ctest)
else()
endif()
