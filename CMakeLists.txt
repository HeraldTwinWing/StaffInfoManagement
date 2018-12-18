cmake_minimum_required(VERSION 3.12)
project(StaffInfoManagement C)

set(CMAKE_C_STANDARD 99)

add_executable(StaffInfoManagement main.c menu.c menu.h stringOperation.c stringOperation.h csvFile.c csvFile.h hash.c hash.h mainFunction.c mainFunction.h)