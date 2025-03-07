cmake_minimum_required(VERSION 3.21)

project(diusTests LANGUAGES CXX)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
    find_package(dius REQUIRED)
    enable_testing()
endif()

# ---- Tests ----

file(GLOB sources CONFIGURE_DEPENDS src/*.cpp)
add_executable(dius_test ${sources})

target_link_libraries(dius_test PRIVATE dius::dius dius::dius_test_main)

add_test(NAME dius_test COMMAND dius_test)

# ---- Fixtures ----

file(GLOB fixtures CONFIGURE_DEPENDS "src/fixtures/*.cpp")

foreach(file ${fixtures})
    get_filename_component(target_name "${file}" NAME_WE)
    add_executable(${target_name} ${file})
    target_link_libraries(${target_name} PRIVATE dius::dius)
endforeach()

if(CMAKE_CROSSCOMPILING)
    target_compile_definitions(dius_test PRIVATE FIXTURE_PATH="/")
else()
    target_compile_definitions(dius_test PRIVATE FIXTURE_PATH="${CMAKE_CURRENT_BINARY_DIR}/")
endif()
