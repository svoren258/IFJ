cmake_minimum_required(VERSION 3.3)
project(projekt_IFJ)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")

set(SOURCE_FILES main.c)
add_executable(projekt_IFJ ${SOURCE_FILES} main.c)