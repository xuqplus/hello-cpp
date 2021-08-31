cmake_minimum_required(VERSION 3.0.0)
project(include-curl VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(include-curl main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# try to find one file in PATHS which matches the NAMES
find_file(TEST_FIND_FILE
    NAMES CMakeLists.txt main.cpp
    PATHS . .. ../../
)
message(TEST_FIND_FILE " -> " ${TEST_FIND_FILE})

# try to find one library in PATHS which matches the NAMES
add_library(test-lib main.cpp)
find_library(TEST_FIND_LIB
    NAMES test-lib test-lib2 libhello-static-lib.a
    PATHS . .. ../../ ${CMAKE_INSTALL_PREFIX}/lib/hello-static-lib/
)
message(CMAKE_INSTALL_PREFIX " -> " ${CMAKE_INSTALL_PREFIX})
message(TEST_FIND_LIB " -> " ${TEST_FIND_LIB})

# link the library finded
target_link_libraries(include-curl ${TEST_FIND_LIB})

