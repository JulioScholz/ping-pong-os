cmake_minimum_required(VERSION 3.14)
project(p04 C)

set(CMAKE_C_STANDARD 99)

add_executable(p04 queue.h queue.c datatypes.h pingpong.h pingpong.c pingpong-scheduler.c)

#add_executable(p04 queue.h datatypes.h pingpong.h pingpong.c queue.c)

