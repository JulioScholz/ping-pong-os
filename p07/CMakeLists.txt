cmake_minimum_required(VERSION 3.14)
project(p07 C)

set(CMAKE_C_STANDARD 99)

add_executable(p07 pingpong-maintask.c datatypes.h pingpong.c pingpong.h queue.c queue.h)