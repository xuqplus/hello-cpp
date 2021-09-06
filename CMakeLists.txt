cmake_minimum_required(VERSION 3.10.0)
project(hello-cpp VERSION 1.2.3)

set(CONFIG_FILE config.h)
configure_file(${CONFIG_FILE}.in ${CONFIG_FILE})

include(CTest)
enable_testing()

if(${CMAKE_SYSTEM} MATCHES WSL2|Linux)
    message("CMAKE_SYSTEM .. -> " ${CMAKE_SYSTEM})
    # link_libraries(/usr/lib/x86_64-linux-gnu/libcurl.so)
    # include_directories(/usr/share/x86_64-linux-gnu/)
    # include static/shared headers
    include_directories(${CMAKE_INSTALL_PREFIX}/include/hello-static-lib)
    include_directories(${CMAKE_INSTALL_PREFIX}/include/hello-shared-lib)
    # link static/shared libs
    link_libraries(${CMAKE_INSTALL_PREFIX}/lib/hello-static-lib/libhello-static-lib.a)
    link_libraries(${CMAKE_INSTALL_PREFIX}/share/libhello-shared-lib.so)
elseif(${CMAKE_SYSTEM} MATCHES Windows)
    message("Windows .. -> " ${CMAKE_SYSTEM})
    
# include vcpkg before add executable
set(VCPKG_DIRECTORY D:/softapp/vcpkg)
include(${VCPKG_DIRECTORY}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_INSTALL_PREFIX ${VCPKG_DIRECTORY}/installed/x64-windows)

# include static / shared libraries
## after include_directories we can run `cmake ..` successfully in `build` directory
include_directories(${CMAKE_INSTALL_PREFIX}/include/hello-static-lib)
## after link_libraries `make` directive success
link_libraries(${CMAKE_INSTALL_PREFIX}/lib/hello-static-lib/libhello-static-lib.a)
## use shared lib
include_directories(${CMAKE_INSTALL_PREFIX}/include/hello-shared-lib)
link_libraries(${CMAKE_INSTALL_PREFIX}/share/hello-shared-lib/libhello-shared-lib.dll.a)
link_libraries(${CMAKE_INSTALL_PREFIX}/bin/libhello-shared-lib.dll)

endif()

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

find_package(CURL MODULE REQUIRED)
# find_library(
#    CURL_LIBRARIES
#    NAMES libcurl.so
#    PATHS /usr/lib/x86_64-linux-gnu
# )
target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
# or below line use namespace when link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)

# test cmake install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${PROJECT_BINARY_DIR}/config.h DESTINATION include)

# print messages
message(VCPKG_DIRECTORY " -> " ${VCPKG_DIRECTORY})
message(CURL " -> " ${CURL})
message(CURL_FOUND " -> " ${CURL_FOUND})
message(CURL_LIBRARIES " -> " ${CURL_LIBRARIES})
message(CURL_INCLUDE_DIRS " -> " ${CURL_INCLUDE_DIRS})
message(CURL_VERSION_STRING " -> " ${CURL_VERSION_STRING})
message(PC_CURL_INCLUDE_DIRS " -> " ${PC_CURL_INCLUDE_DIRS})
message(FindPkgConfig " -> " ${FindPkgConfig})
## project related variables
message(PROJECT_NAME " -> " ${PROJECT_NAME})
message(PROJECT_VERSION " -> " ${PROJECT_VERSION})
message(PROJECT_BINARY_DIR " -> " ${PROJECT_BINARY_DIR})
message(CMAKE_SYSTEM " -> " ${CMAKE_SYSTEM})
