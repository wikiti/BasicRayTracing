cmake_minimum_required(VERSION 3.0.0)

project(RayTracingInOneWeekend VERSION 0.0.1)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

add_executable(RayTracingInOneWeekend ${SRC_FILES})

target_include_directories(RayTracingInOneWeekend PUBLIC include)
