cmake_minimum_required(VERSION 3.0.0)

project(RayTraycingInOneWeekend VERSION 0.0.1)

add_executable(RayTraycingInOneWeekend src/main.cpp src/progress.cpp src/vector3.cpp)

target_include_directories(RayTraycingInOneWeekend PUBLIC include)
