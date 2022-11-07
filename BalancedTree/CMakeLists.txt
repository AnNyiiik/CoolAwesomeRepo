cmake_minimum_required(VERSION 3.21)
project(BalancedTree C)

set(CMAKE_C_STANDARD 23)

add_executable(BalancedTree main.c "../BinaryTree/tree.c" "../BinaryTree/test.c")
