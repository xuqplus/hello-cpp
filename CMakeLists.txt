cmake_minimum_required(VERSION 3.20.0)
project(hello-cpp VERSION 1.2.3)

set(CONFIG_FILE config.h)
configure_file(${CONFIG_FILE}.in ${CONFIG_FILE})

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
add_executable(hello-test test.cpp)
add_test(test1 hello-test)
add_test(test2 hello-test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# help to include config.h which's created by cmake
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# set cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# compile option / conditional compilation
## try use `cmake .. -DUSE_MY_LIB=off` when build
option(USE_MY_LIB "Whether use my lib or not" on)

if (USE_MY_LIB)
    # add subdirectory
    add_subdirectory(MyLib)
    ## add search path for header ?
    target_link_libraries(${PROJECT_NAME} PUBLIC my-lib)
    ## add search path for library ?
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/MyLib)
    ## list for what ? - a data structure / a data contrainer ..
    list(APPEND extra_libs my-lib)
    list(APPEND extra_libs my-lib)
    # list(APPEND extra_includes MyLib)
    message(extra_libs -> ${extra_libs})
    # message(extra_includes -> ${extra_includes})
endif()

# use interface to add library
add_subdirectory(my-lib2)
target_link_libraries(${PROJECT_NAME} PRIVATE my-lib2)

set(VCPKG_DIRECTORY D:/softapp/vcpkg)

include(${VCPKG_DIRECTORY}/scripts/buildsystems/vcpkg.cmake)
find_package(CURL CONFIG REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
# target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)

# test cmake install
set(CMAKE_INSTALL_PREFIX ${VCPKG_DIRECTORY}/installed/x64-windows)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${PROJECT_BINARY_DIR}/config.h DESTINATION include)

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