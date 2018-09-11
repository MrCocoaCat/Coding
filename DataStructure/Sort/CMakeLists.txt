cmake_minimum_required(VERSION 3.9)
project(Sort)

set(CMAKE_CXX_STANDARD 11)

add_executable(BinaryChop BinaryChop.c)

add_executable( BubbleSort  BubbleSort.cpp)

add_executable( compare_BubbleSort  compare_BubbleSort.cpp)

add_executable( QuickSort2  QuickSort2.cpp)

add_executable( QuickSort3  QuickSort3.cpp)

add_executable( QuickSort4  QuickSort4.cpp)

add_executable( InsertSort  InsertSort.c)