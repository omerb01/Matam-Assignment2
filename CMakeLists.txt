cmake_minimum_required(VERSION 3.8)
project(Assinment2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES DynamicArray.c)
set(SOURCE_FILES main.c Course.c main.c)
add_executable(Assinment2 ${SOURCE_FILES})

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -pedantic")