cmake_minimum_required(VERSION 3.21)
project(SymmetricList C)

set(CMAKE_C_STANDARD 23)

add_executable(SymmetricList main.c "../List/list.c" "../BinaryTree/tree.c")
