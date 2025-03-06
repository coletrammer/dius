add_custom_target(
    check_tidy
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMAND /bin/sh -c "'${CMAKE_SOURCE_DIR}/meta/scripts/run-clang-tidy.sh' check '$$DIUS_TIDY_ARGS'"
    USES_TERMINAL
)

add_custom_target(
    tidy
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMAND /bin/sh -c "'${CMAKE_SOURCE_DIR}/meta/scripts/run-clang-tidy.sh' tidy '$$DIUS_TIDY_ARGS'"
    USES_TERMINAL
)

add_custom_target(
    clang_analyze
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMAND /bin/sh -c "'${CMAKE_SOURCE_DIR}/meta/scripts/run-clang-tidy.sh' analyze '$$DIUS_TIDY_ARGS'"
    USES_TERMINAL
)
