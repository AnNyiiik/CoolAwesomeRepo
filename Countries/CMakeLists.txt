cmake_minimum_required(VERSION 3.21)
project(Countries C)

set(CMAKE_C_STANDARD 23)

set(Headers "matrixFunctions.h" "../List/list.h")

add_executable(Countries main.c cmake-build-debug/matrixFunctions.c cmake-build-debug/matrixFunctions.h "../List/list.c")
