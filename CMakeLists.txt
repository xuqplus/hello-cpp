cmake_minimum_required(VERSION 3.20.0)
project(hello-cpp VERSION 0.1.0)

set(CONFIG_FILE config.h)
configure_file(${CONFIG_FILE}.in ${CONFIG_FILE})

include(CTest)
enable_testing()

add_executable(hello-cpp main.cpp)
add_executable(hello-test test.cpp)
add_test(test1 hello-test)
add_test(test2 hello-test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# help to include config.h which's created by cmake
target_include_directories(hello-cpp PUBLIC ${PROJECT_BINARY_DIR})

set(VCPKG_DIRECTORY D:/softapp/vcpkg)

include(${VCPKG_DIRECTORY}/scripts/buildsystems/vcpkg.cmake)
find_package(CURL CONFIG REQUIRED)
target_link_libraries(hello-cpp PRIVATE ${CURL_LIBRARIES})
# target_link_libraries(hello-cpp PRIVATE CURL::libcurl)

# print messages
message(VCPKG_DIRECTORY " -> " ${VCPKG_DIRECTORY})
message(CURL " -> " ${CURL})
message(CURL_FOUND " -> " ${CURL_FOUND})
message(CURL_LIBRARIES " -> " ${CURL_LIBRARIES})
message(CURL_INCLUDE_DIRS " -> " ${CURL_INCLUDE_DIRS})
message(CURL_VERSION_STRING " -> " ${CURL_VERSION_STRING})
## project related variables
message(PROJECT_NAME " -> " ${PROJECT_NAME})
message(PROJECT_VERSION " -> " ${PROJECT_VERSION})
message(PROJECT_BINARY_DIR " -> " ${PROJECT_BINARY_DIR})