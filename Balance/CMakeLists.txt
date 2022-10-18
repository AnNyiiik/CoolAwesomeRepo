cmake_minimum_required(VERSION 3.21)
project(Balance C)

set(CMAKE_C_STANDARD 23)

add_executable(Balance main.c ../StackModule/stack.c ../StackModule/test.c)
