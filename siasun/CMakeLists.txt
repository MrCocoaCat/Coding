cmake_minimum_required(VERSION 3.5)
project(siasun)
set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )

set(CMAKE_CXX_STANDARD 11)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )

add_executable(myfind main.cpp)

