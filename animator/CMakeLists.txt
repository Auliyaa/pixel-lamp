cmake_minimum_required(VERSION 3.21.0)

project(animator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)
find_package(OpenCV COMPONENTS core imgcodecs imgproc photo REQUIRED)
add_executable(animator animator.cpp)
target_link_libraries(animator PUBLIC opencv_core opencv_imgcodecs opencv_imgproc opencv_photo OpenMP::OpenMP_CXX)
