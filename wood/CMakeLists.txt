cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(nefu)

find_package(PCL 1.2 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (filter extract_indices.cpp )
target_link_libraries (filter ${PCL_LIBRARIES})


add_executable (Triangulation  Triangulation.cpp )
target_link_libraries (Triangulation ${PCL_LIBRARIES})

add_executable (possion   possion.cpp)
target_link_libraries (possion ${PCL_LIBRARIES})

add_executable (etra   etra.cpp)
target_link_libraries (etra ${PCL_LIBRARIES})


set(FUNCTIONS functions.h functions.cpp)

#设置源文件
set(FEATURES_SRC_FILES features.cpp ${FUNCTIONS})

add_executable(feature_detection ${FEATURES_SRC_FILES})
# 链接OpenCV库文件倒应用程序
target_link_libraries(feature_detection ${OpenCV_LIBS})


set(BFM_MATCHING_SRC_FILES bfm_matcher.cpp ${FUNCTIONS})
add_executable(bfm_matcher ${BFM_MATCHING_SRC_FILES})
target_link_libraries(bfm_matcher ${OpenCV_LIBS})

set(KNN_MATCHING_SRC_FILES knn_matcher.cpp ${FUNCTIONS})
add_executable(knn_matcher ${KNN_MATCHING_SRC_FILES})
target_link_libraries(knn_matcher ${OpenCV_LIBS})