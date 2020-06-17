cmake_minimum_required(VERSION 3.0.0)

project(BasicRayTracing VERSION 0.0.1)

find_package (Threads REQUIRED)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

add_executable(BasicRayTracing ${SRC_FILES})

target_include_directories(BasicRayTracing PUBLIC include)
target_link_libraries(BasicRayTracing ${CMAKE_THREAD_LIBS_INIT})
