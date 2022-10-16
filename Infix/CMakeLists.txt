cmake_minimum_required(VERSION 3.21)
project(Infix C)

set(CMAKE_C_STANDARD 23)

add_executable(Infix main.c "../StackModule/stack.c")
