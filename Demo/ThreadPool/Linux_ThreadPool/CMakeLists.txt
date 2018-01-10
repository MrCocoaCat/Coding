cmake_minimum_required(VERSION 3.5)
project(Linux_ThreadPool)


set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )

add_executable(Linux_ThreadPool
        main.cpp
        MyLock.h
        ThreadPool.cpp
        ThreadPool.h)
