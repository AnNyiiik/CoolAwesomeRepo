cmake_minimum_required(VERSION 3.21)
project(HashTable C)

set(CMAKE_C_STANDARD 23)

add_executable(HashTable main.c hashTable.c hashTable.h "../List/list.c")
