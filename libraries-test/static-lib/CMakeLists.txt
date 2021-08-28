cmake_minimum_required(VERSION 3.20.0)
project(hello-static-lib VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(hello-static-lib STATIC hello-static-lib.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable(test1 main.cpp)
add_test(test test1)

# set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(VCPKG_DIRECTORY D:/softapp/vcpkg)
set(CMAKE_INSTALL_PREFIX ${VCPKG_DIRECTORY}/installed/x64-windows)
install(
    TARGETS hello-static-lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/${PROJECT_NAME}
)
install(FILES hello-static-lib.h DESTINATION include/${PROJECT_NAME})

