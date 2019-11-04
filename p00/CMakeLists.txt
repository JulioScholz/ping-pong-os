cmake_minimum_required(VERSION 3.14)
project(p00 C)

set(CMAKE_C_STANDARD 99)

add_executable(p00 queue.h queue.c testafila.c)