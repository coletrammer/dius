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

# ---- Declare library ----

add_library(dius_dius INTERFACE)
add_library(dius::dius ALIAS dius_dius)

set_property(TARGET dius_dius PROPERTY EXPORT_NAME di)

target_include_directories(dius_dius ${warning_guard} INTERFACE "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")

file(GLOB_RECURSE headers CONFIGURE_DEPENDS include/*.h)
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

target_compile_options(dius_dius INTERFACE -std=gnu++26)
target_compile_options(dius_dius INTERFACE -fno-exceptions -fno-rtti)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(meta/cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT di_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(AUTHOR_WARNING "Developer mode is intended for developers of dius")
endif()

include(meta/cmake/dev-mode.cmake)
