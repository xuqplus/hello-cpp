cmake_minimum_required(VERSION 3.0.0)
project(hello-cpp VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(hello-cpp main.cpp)
add_executable(hello-test test.cpp)
add_test(test1 hello-test)
add_test(test2 hello-test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
