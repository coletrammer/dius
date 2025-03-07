cmake_minimum_required(VERSION 3.21)

include(meta/cmake/prelude.cmake)

project(
    dius
    VERSION 0.1.0
    DESCRIPTION "A cross-platform C++ platform runtime library"
    HOMEPAGE_URL "https://coletrammer.github.io/dius"
    LANGUAGES CXX
)

include(meta/cmake/variables.cmake)

# ---- Dependencies ----

# Ensure drop verify interface header sets for our dependencies.
set(want_header_set_verification ${CMAKE_VERIFY_INTERFACE_HEADER_SETS})
set(CMAKE_VERIFY_INTERFACE_HEADER_SETS OFF)

set(dius_di_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/di"
    CACHE STRING "Directory containing the di library"
)

if(EXISTS "${dius_di_DIRECTORY}")
    message(STATUS "Found di dependency at ${dius_di_DIRECTORY}")
    add_subdirectory("${dius_di_DIRECTORY}")
else()
    message(STATUS "Looking for di library via find_package()")
    find_package(di REQUIRED)
endif()

# Restore verify interface header sets
set(CMAKE_VERIFY_INTERFACE_HEADER_SETS ${want_header_set_verification})

# ---- Source files ----

function(filter input exclude_list output)
    foreach(exclude ${exclude_list})
        string(TOLOWER ${exclude} exclude)
        list(FILTER input EXCLUDE REGEX ${exclude})
    endforeach()

    set(${output}
        ${input}
        PARENT_SCOPE
    )
endfunction()

file(
    GLOB_RECURSE sources CONFIGURE_DEPENDS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "src/*.cpp"
)
file(
    GLOB_RECURSE headers CONFIGURE_DEPENDS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "include/*.h"
)

set(to_filter x86_64 posix linux runtime test_main)
list(REMOVE_ITEM to_filter ${CMAKE_HOST_SYSTEM_PROCESSOR})

list(REMOVE_ITEM to_filter linux)
if(UNIX AND NOT IROS_UseDiusRuntime)
    list(REMOVE_ITEM to_filter posix)
endif()
if(IROS_UseDiusRuntime)
    list(REMOVE_ITEM to_filter runtime)
endif()

filter("${sources}" "${to_filter}" sources)
filter("${headers}" "${to_filter}" headers)

# ---- Declare library ----

add_library(dius_dius ${sources})
add_library(dius::dius ALIAS dius_dius)

set_target_properties(
    dius_dius
    PROPERTIES VERSION "${PROJECT_VERSION}"
               SOVERSION "${PROJECT_VERSION_MAJOR}"
               OUTPUT_NAME dius
               EXPORT_NAME dius
)

target_include_directories(dius_dius ${warning_guard} PUBLIC "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")

# di is a interface dependency, as our header files depend on it.
target_link_libraries(dius_dius PUBLIC di::di)
target_compile_definitions(dius_dius PUBLIC DI_CUSTOM_ASSERT_HANDLER DI_CUSTOM_PLATFORM=<dius/platform.h>)

target_sources(
    dius_dius
    INTERFACE FILE_SET
              HEADERS
              TYPE
              HEADERS
              BASE_DIRS
              include
              FILES
              ${headers}
)

# ---- Declare unit test library main function ----

file(
    GLOB_RECURSE test_main_sources CONFIGURE_DEPENDS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "src/test_main/*.cpp"
)

add_library(dius_dius_test_main ${test_main_sources})
add_library(dius::dius_test_main ALIAS dius_dius_test_main)

target_link_libraries(dius_dius_test_main PRIVATE di::di dius_dius)

set_target_properties(
    dius_dius_test_main
    PROPERTIES VERSION "${PROJECT_VERSION}"
               SOVERSION "${PROJECT_VERSION_MAJOR}"
               OUTPUT_NAME dius_test_main
               EXPORT_NAME dius_test_main
)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(meta/cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT dius_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(AUTHOR_WARNING "Developer mode is intended for developers of dius")
endif()

include(meta/cmake/dev-mode.cmake)
