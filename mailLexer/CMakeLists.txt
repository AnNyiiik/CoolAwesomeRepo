cmake_minimum_required(VERSION 3.21)
project(mailLexer C)

set(CMAKE_C_STANDARD 23)

add_executable(mailLexer main.c lexer.c lexer.h)
