cmake_minimum_required(VERSION 3.21)
project(ExpressionTree C)

set(CMAKE_C_STANDARD 23)

add_executable(ExpressionTree main.c cmake-build-debug/expression.c cmake-build-debug/expression.h expression.c)
