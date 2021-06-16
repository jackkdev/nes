#
#  Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
#

cmake_minimum_required(VERSION 3.19)

project(nes)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/googletest)

add_subdirectory(nes)
