cmake_minimum_required(VERSION 3.21)
project(List C)

set(CMAKE_C_STANDARD 23)

add_executable(List main.c list.c list.h test.c test.h )
