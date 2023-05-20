cmake_minimum_required(VERSION 3.10)

project(VARIABLE_INTEGER)


add_subdirectory(Catch2)
add_library(vintlib impl_VInt.cpp)


add_executable(tests tests.cpp)
target_link_libraries(tests vintlib Catch2::Catch2WithMain)

enable_testing()

add_test(
    NAME tests
    COMMAND $<TARGET_FILE:tests>
)
