cmake_minimum_required(VERSION 3.8)
project(dumbot)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)
include_directories(/usr/local/include/lua53)
link_directories(/usr/local/lib)

set(SOURCE_FILES main.cpp)
add_executable(dumbot ${SOURCE_FILES})