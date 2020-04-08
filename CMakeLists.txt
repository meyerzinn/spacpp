cmake_minimum_required(VERSION 3.15)
project(spacpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(EnTT CONFIG REQUIRED)

find_path(QUADTREE_INCLUDE_DIR quadtree/Quadtree.h)
include_directories(${QUADTREE_INCLUDE_DIR})

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(unofficial-libuv CONFIG REQUIRED)

find_path(UWEBSOCKETS_INCLUDE_DIR uwebsockets/App.h)
include_directories(${UWEBSOCKETS_INCLUDE_DIR})

find_path(USOCKETS_INCLUDE_DIR libusockets.h)
find_library(USOCKETS_LIBRARY libuSockets)
include_directories(${USOCKETS_INCLUDE_DIR})
link_libraries(${USOCKETS_LIBRARY})

add_executable(spacpp main.cpp vec2.h util.h)

target_link_libraries(spacpp PRIVATE EnTT::EnTT)
target_link_libraries(spacpp PRIVATE ZLIB::ZLIB)
target_link_libraries(spacpp PRIVATE unofficial::libuv::libuv)

#target_link_libraries(spacpp PRIVATE ${UWEBSOCKETS_LIBRARY})
#target_include_directories(spacpp ${UWEBSOCKETS_INCLUDE_DIR})