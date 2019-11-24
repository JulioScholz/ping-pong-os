cmake_minimum_required(VERSION 3.14)
project(p09 C)

set(CMAKE_C_STANDARD 99)

add_executable(p09 queue.c queue.h pingpong-sleep.c pingpong.c pingpong.h)