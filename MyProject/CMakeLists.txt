cmake_minimum_required(VERSION 3.21)
project(MyProject C)

set(CMAKE_C_STANDARD 23)

add_executable(MyProject main.c MatrixFunctions.c MatrixFunctions.h "../List/list.c")
