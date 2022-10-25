cmake_minimum_required(VERSION 3.21)
project(roundKilling C)

set(CMAKE_C_STANDARD 23)

add_executable(roundKilling main.c "../CycleList/cycleList.c" "../CycleList/test.c")
