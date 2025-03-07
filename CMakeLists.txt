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

# Drop verify interface header sets for our dependencies.
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

# Restore verify interface header sets.
set(CMAKE_VERIFY_INTERFACE_HEADER_SETS ${want_header_set_verification})

# ---- Source files ----

# All files in certain directories will be filtered out based on the configuration, target OS, and target architecture.
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

# Keep any source files for the target system and architecture.
string(TOLOWER "${CMAKE_SYSTEM_NAME}" system_name)
list(REMOVE_ITEM to_filter ${system_name})
list(REMOVE_ITEM to_filter ${CMAKE_SYSTEM_PROCESSOR})

# Use either the dius runtime or posix base depending on the configuration.
if(dius_USE_RUNTIME)
    list(REMOVE_ITEM to_filter runtime)
elseif(UNIX)
    list(REMOVE_ITEM to_filter posix)
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

# ---- Dius runtime support ----
if(dius_USE_RUNTIME)
    # Crt0 is provided to allow using the dius runtime with a regular linux compiler, which expects crt0.o to exist even
    # with no libc.
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/crt0.o" "INPUT(libdius.a)")

    target_compile_definitions(dius_dius PUBLIC DIUS_USE_RUNTIME DI_NO_USE_STD)

    # The dius runtime is fully free standing and requires consumers to not link libc, or use standard C++ headers.
    target_compile_options(
        dius_dius
        PUBLIC "-nostdlib" "-static"
        PRIVATE "-fno-stack-protector" "-ffreestanding" "-fPIC"
    )
    target_link_options(
        dius_dius
        PUBLIC
        "-nostdlib"
        "-static"
        PRIVATE
        "-fno-stack-protector"
        "-ffreestanding"
    )
endif()

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
