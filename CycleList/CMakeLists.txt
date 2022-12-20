cmake_minimum_required(VERSION 3.21)
project(CycleList C)

set(CMAKE_C_STANDARD 23)

add_executable(CycleList main.c cycleList.c cycleList.h test.c test.h)
