cmake_minimum_required(VERSION 3.10)
project(spacpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(spacpp main.cpp vec2.h util.h physics.h net.h packets_generated.h)

find_package(Boost 1.72 REQUIRED COMPONENTS fiber)
find_package(EnTT CONFIG REQUIRED)
find_package(Flatbuffers CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(unofficial-libuv CONFIG REQUIRED)
find_path(USOCKETS_INCLUDE_DIR libusockets.h)
find_path(QUADTREE_INCLUDE_DIR quadtree/Quadtree.h)
find_path(UWEBSOCKETS_INCLUDE_DIR uwebsockets/App.h)

find_library(USOCKETS_LIBRARY libuSockets.a)

target_include_directories(spacpp PRIVATE ${USOCKETS_INCLUDE_DIR} ${UWEBSOCKETS_INCLUDE_DIR} ${QUADTREE_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
target_link_libraries(spacpp PRIVATE ${USOCKETS_LIBRARY} EnTT::EnTT flatbuffers::flatbuffers ZLIB::ZLIB unofficial::libuv::libuv ${Boost_LIBRARIES})

#target_link_libraries(spacpp PRIVATE ${UWEBSOCKETS_LIBRARY})
#target_include_directories(spacpp ${UWEBSOCKETS_INCLUDE_DIR})