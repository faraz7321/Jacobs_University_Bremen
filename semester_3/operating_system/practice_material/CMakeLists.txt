# 
# scat/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.1)

project(SCAT C) 
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_definitions(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(scat scat.c)
