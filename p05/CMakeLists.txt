cmake_minimum_required(VERSION 3.14)
project(p05 C)

set(CMAKE_C_STANDARD 99)

add_executable(p05 queue.h queue.c datatypes.h pingpong.h pingpong.c pingpong-preempcao.c signal.c timer.c)

#add_executable(p04 queue.h datatypes.h pingpong.h pingpong.c queue.c)

