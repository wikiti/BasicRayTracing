cmake_minimum_required(VERSION 3.0.0)

project(RayTraycingInOneWeekend VERSION 0.0.1)

add_executable(
  RayTraycingInOneWeekend
  src/color.cpp
  src/hit_info.cpp
  src/hittable_list.cpp
  src/main.cpp
  src/progress.cpp
  src/ray.cpp
  src/sphere.cpp
  src/utils.cpp
  src/vector3.cpp
)

target_include_directories(RayTraycingInOneWeekend PUBLIC include)
