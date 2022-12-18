cmake_minimum_required(VERSION 3.21)
project(lexerRealNumbers C)

set(CMAKE_C_STANDARD 23)

add_executable(lexerRealNumbers main.c lexer.c lexer.h test.c test.h)
