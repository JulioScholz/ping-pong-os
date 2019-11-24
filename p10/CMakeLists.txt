cmake_minimum_required(VERSION 3.14)
project(p10 C)

set(CMAKE_C_STANDARD 99)

add_executable(p10 pingpong.h pingpong.c pingpong-racecond.c pingpong-semaphore.c datatypes.h queue.c queue.h)