# Use Drogon web application framework
https://github.com/drogonframework/drogon

## install dependencies
`apt install -y cmake build-essential gdb libssl-dev libjsoncpp-dev uuid-dev libzzip-dev zlib1g-dev`

## build
`./build.sh`

## make & install
`make && make install`

## reference 
`find_package(Drogon)` or `find_package(Drogon CONFIG)` + `target_link_libraries(target ${DROGON_LIBRARIES})`
