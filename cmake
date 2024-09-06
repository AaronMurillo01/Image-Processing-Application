cmake_minimum_required(VERSION 3.10)
project(ImageProcessingApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(image_processor image_processor.cpp)
target_link_libraries(image_processor ${OpenCV_LIBS})