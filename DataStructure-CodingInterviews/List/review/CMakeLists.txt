cmake_minimum_required(VERSION 3.9)
project(review)

set(CMAKE_CXX_STANDARD 11)

add_executable(CreateNode CreateNode.cpp main.cpp)
add_executable(ReList CreateNode.cpp ReList.cpp)

add_executable(mergeTwoList CreateNode.cpp mergeTwoList.cpp)