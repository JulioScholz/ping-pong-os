cmake_minimum_required(VERSION 3.14)
project(p06 C)

set(CMAKE_C_STANDARD 99)

add_executable(p06 pingpong-contab.c datatypes.h pingpong.c pingpong.h queue.c queue.h)