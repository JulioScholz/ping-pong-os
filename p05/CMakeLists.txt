cmake_minimum_required(VERSION 3.14)
project(p05 C)

set(CMAKE_C_STANDARD 99)

add_executable(p05 queue.h queue.c timer.c signal.c pingpong.c pingpong.h datatypes.h pingpong-preempcao.c)