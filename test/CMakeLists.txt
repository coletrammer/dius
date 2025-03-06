file(GLOB sources CONFIGURE_DEPENDS *.cpp)
list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/test_process_arg_passing_fixture.cpp)
add_executable(dius_test ${sources})

find_package(Dius REQUIRED)

target_link_libraries(dius_test PRIVATE Dius::dius Dius::dius_test_main)

if(CMAKE_CROSSCOMPILING)
    target_compile_definitions(dius_test PRIVATE FIXTURE_PATH="/")
else()
    target_compile_definitions(dius_test PRIVATE FIXTURE_PATH="${CMAKE_CURRENT_BINARY_DIR}/")
endif()

add_executable(dius_test_process_arg_passing_fixture test_process_arg_passing_fixture.cpp)

target_link_libraries(dius_test_process_arg_passing_fixture PRIVATE Dius::dius)

add_test(NAME dius_test COMMAND dius_test)
