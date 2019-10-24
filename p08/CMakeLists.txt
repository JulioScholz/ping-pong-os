cmake_minimum_required(VERSION 3.14)
project(p08 C)

set(CMAKE_C_STANDARD 99)

add_executable(p08 pingpong.h pingpong.c datatypes.h queue.h queue.c pingpong-join.c)