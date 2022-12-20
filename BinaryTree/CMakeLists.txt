cmake_minimum_required(VERSION 3.21)
project(BinaryTree C)

set(CMAKE_C_STANDARD 23)

add_executable(BinaryTree main.c tree.c tree.h test.c test.h)
