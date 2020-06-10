cmake_minimum_required(VERSION 3.0.0)

project(RayTracingInOneWeekend VERSION 0.0.1)

add_executable(
  RayTracingInOneWeekend

  src/main.cpp

  src/rtiow/color.cpp
  src/rtiow/hit_info.cpp
  src/rtiow/hittable_list.cpp
  src/rtiow/progress.cpp
  src/rtiow/ray.cpp
  src/rtiow/sphere.cpp
  src/rtiow/utils.cpp
  src/rtiow/vector3.cpp
)

target_include_directories(RayTracingInOneWeekend PUBLIC include)
