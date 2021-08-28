add_library(my-lib my-lib.cpp)

# test cmake install
install(TARGETS my-lib DESTINATION lib)
install(FILES my-lib.h DESTINATION include)