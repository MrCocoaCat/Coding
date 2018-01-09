cmake_minimum_required(VERSION 3.5)
project(siasun)


set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread -O0 -ggdb" )
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_executable(siasun main1.cpp MyLock.h ThreadPool.cpp ThreadPool.h
        )