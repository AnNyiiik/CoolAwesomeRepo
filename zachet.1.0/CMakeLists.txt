cmake_minimum_required(VERSION 3.21)
project(zachet_1_0 C)

set(CMAKE_C_STANDARD 23)

add_executable(zachet_1_0 main.c "../List/list.c" "../List/test.c")
