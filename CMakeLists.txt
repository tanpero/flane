cmake_minimum_required(VERSION 3.10) # 指定CMake的最低版本要求

project(Flane)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src/compiler)

file(GLOB_RECURSE SOURCES "src/compiler/*.cc")
file(GLOB_RECURSE HEADERS "src/compiler/*.hh")

add_executable(flane ${SOURCES} ${HEADERS})
