cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(tuto-pairwise)
find_package(PCL 1.4 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})

link_directories(${PCL_LIBRARY_DIRS})		
add_definitions(${PCL_DEFINITIONS})

add_executable (pairwise_incremental_registration pairwise_incremental_registration.cpp)
target_link_libraries (pairwise_incremental_registration ${PCL_LIBRARIES})

add_executable (icp2 icp2.cpp)
target_link_libraries (icp2 ${PCL_LIBRARIES})



add_executable (icp1 icp1.cpp)
target_link_libraries (icp1 ${PCL_LIBRARIES})