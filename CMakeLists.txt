cmake_minimum_required(VERSION 3.19)

project(
    nes
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

add_subdirectory(nes)