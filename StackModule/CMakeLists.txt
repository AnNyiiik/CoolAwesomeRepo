cmake_minimum_required(VERSION 3.21)
project(StackModule C)

set(CMAKE_C_STANDARD 23)

add_executable(StackModule main.c stack.h stack.c test.c test.h)
