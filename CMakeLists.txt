cmake_minimum_required(VERSION 3.0.0)

project(BasicRayTracing VERSION 0.0.1)

# Dependencies

include(ExternalProject)

find_package (Threads REQUIRED)

ExternalProject_Add(stb
                    BUILD_COMMAND ""
                    INSTALL_COMMAND ""
                    CONFIGURE_COMMAND ""
                    UPDATE_COMMAND ""
                    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/stb
                    GIT_REPOSITORY "https://github.com/nothings/stb.git"
                    GIT_TAG "master")

# File globs and copies

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Main executable and dependencies

add_executable(BasicRayTracing ${SRC_FILES})

add_dependencies(BasicRayTracing stb)

target_include_directories(BasicRayTracing PRIVATE
                           include
                           ${CMAKE_BINARY_DIR}/thirdparty/stb/src/stb)

target_link_libraries(BasicRayTracing ${CMAKE_THREAD_LIBS_INIT})
