# ---- Developer mode ----

# Developer mode enables targets and code paths in the CMake scripts that are only relevant for the developer(s) of di
# Targets necessary to build the project must be provided unconditionally, so consumers can trivially build and package
# the project
if(PROJECT_IS_TOP_LEVEL)
    option(dius_DEVELOPER_MODE "Enable developer mode" OFF)
endif()

# ---- Warning guard ----

# target_include_directories with the SYSTEM modifier will request the compiler to omit warnings from the provided
# paths, if the compiler supports that. This is to provide a user experience similar to find_package when
# add_subdirectory or FetchContent is used to consume this project
set(warning_guard "")
if(NOT PROJECT_IS_TOP_LEVEL)
    option(dius_INCLUDES_WITH_SYSTEM "Use SYSTEM modifier for dius's includes, disabling warnings" ON)
    mark_as_advanced(dius_INCLUDES_WITH_SYSTEM)
    if(dius_INCLUDES_WITH_SYSTEM)
        set(warning_guard SYSTEM)
    endif()
endif()

# ---- Platform specific values ----

string(TOLOWER "${CMAKE_SYSTEM_NAME}" system_name)
set(dius_PLATFORM
    "${system_name}"
    CACHE STRING "Dius platform name (darwin or linux)"
)

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" processor_name)
set(dius_ARCH
    "${processor_name}"
    CACHE STRING "Dius architecture name (x86_64 or arm64)"
)

# ---- Dius Runtime ----

option(dius_USE_RUNTIME "Enable dius runtime (no libc mode) (linux only)" OFF)
