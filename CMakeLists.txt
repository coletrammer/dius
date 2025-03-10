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

# ---- Declare library ----

add_library(dius_dius)
add_library(dius::dius ALIAS dius_dius)

set_target_properties(
    dius_dius
    PROPERTIES VERSION "${PROJECT_VERSION}"
               SOVERSION "${PROJECT_VERSION_MAJOR}"
               OUTPUT_NAME dius
               EXPORT_NAME dius
)

# Undefine "linux" on linux... For some reason this definition is set by default. We want to use linux as a namespace in
# certain code.
target_compile_options(dius_dius PUBLIC "-Ulinux")

# di is a public dependency, as our header files depend on it.
target_link_libraries(dius_dius PUBLIC di::di)
target_compile_definitions(dius_dius PUBLIC DI_CUSTOM_ASSERT_HANDLER DI_CUSTOM_PLATFORM=<dius/platform.h>)

# ---- Source files ----

# This logic attempts to select the correct source file for the target configuration, and prevent duplicates. This is
# used to only install relevant headers for the target system and architecture instead of including all library headers.
# In addition, this allows specific platforms to provide custom implementations of behavior.

# For a configuration like linux x86_64 using the dius runtime, the search path for files will look like this:
# cmake-format: off
# runtime/arch/linux/x86_64
# runtime/platform/linux
# runtime/arch/x86_64
# runtime/generic/
# platform/arch/linux/x86_64
# platform/linux
# platform/arch/posix/x86_64
# platform/posix
# arch/x86_64
# generic
# cmake-format: on

# Notice that because linux is a posix like system, we'll fallback to using the posix as a secondary system. And
# everything in runtime/ gets priority over everything else. When the dius runtime is disabled, all files in runtime/
# are ignored.

# The paths are mirrored for both include directories and source directories. The path names for arch + platform
# combinations are a bit awkard, due to CMake disallowing FILE_SET base directories to be children of each other.

set(all_headers)
set(all_sources)
macro(process_prefix prefix)
    set(header_prefix "${PROJECT_SOURCE_DIR}/include/${prefix}")
    set(source_prefix "${PROJECT_SOURCE_DIR}/src/${prefix}")

    # Glob for headers and sources.
    file(
        GLOB_RECURSE headers CONFIGURE_DEPENDS
        RELATIVE "${header_prefix}"
        "${header_prefix}/*.h"
    )
    file(
        GLOB_RECURSE sources CONFIGURE_DEPENDS
        RELATIVE "${source_prefix}"
        "${source_prefix}/*.cpp"
    )

    # Remove all headers and sources which have already appeared.
    list(APPEND all_sources_patterns ${all_sources})
    list(TRANSFORM all_sources_patterns PREPEND "^")
    list(TRANSFORM all_sources_patterns APPEND "$")
    list(JOIN all_sources_patterns "|" all_sources_pattern)
    if(all_sources_pattern)
        list(FILTER sources EXCLUDE REGEX "${all_sources_pattern}")
    endif()

    list(APPEND all_headers_patterns ${all_headers})
    list(TRANSFORM all_headers_patterns PREPEND "^")
    list(TRANSFORM all_headers_patterns APPEND "$")
    list(JOIN all_headers_patterns "|" all_headers_pattern)
    if(all_headers_pattern)
        list(FILTER headers EXCLUDE REGEX "${all_headers_pattern}")
    endif()

    # Remember all seen headers and sources.
    list(APPEND all_sources ${sources})
    list(APPEND all_headers ${headers})

    # Add include directory, which may be empty.
    target_include_directories(dius_dius ${warning_guard} PUBLIC "\$<BUILD_INTERFACE:${header_prefix}>")

    # Add any header files found.
    list(TRANSFORM headers PREPEND "${header_prefix}/")
    target_sources(
        dius_dius
        INTERFACE FILE_SET
                  HEADERS
                  TYPE
                  HEADERS
                  BASE_DIRS
                  "include/${prefix}"
                  FILES
                  ${headers}
    )

    # Add any source files found
    list(TRANSFORM sources PREPEND "${source_prefix}/")
    target_sources(dius_dius PRIVATE ${sources})
endmacro()

# Dius runtime prefixes
if(dius_USE_RUNTIME)
    process_prefix(runtime/arch/${dius_PLATFORM}/${dius_ARCH})
    process_prefix(runtime/platform/${dius_PLATFORM})
    process_prefix(runtime/arch/${dius_ARCH})
    process_prefix(runtime/generic)
endif()

# Platform specific prefixes
process_prefix(platform/arch/${dius_PLATFORM}/${dius_ARCH})
process_prefix(platform/${dius_PLATFORM})

# Add POSIX fallback system if supported
if(UNIX)
    process_prefix(platform/arch/posix/${dius_ARCH})
    process_prefix(platform/posix)
endif()

# Base prefixes
process_prefix(arch/${dius_ARCH})
process_prefix(generic)

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
