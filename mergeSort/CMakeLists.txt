cmake_minimum_required(VERSION 3.21)
project(mergeSort C)

set(CMAKE_C_STANDARD 23)

add_executable(mergeSort main.c sort.c test.c "../List/list.c" "../List/test.c")
