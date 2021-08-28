add_library(my-lib2 my-lib.cpp)

target_include_directories(
    my-lib2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)