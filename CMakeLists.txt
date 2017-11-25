cmake_minimum_required(VERSION 3.8)
project(Assinment2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES test1.c Course.c Course.h DynamicArray.h DynamicArray.c CourseSystem.h CourseSystem.c)

add_executable(Assinment2 ${SOURCE_FILES})

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -pedantic")