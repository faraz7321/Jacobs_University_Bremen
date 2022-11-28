# 
# cat++/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(CATPP C) 
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(cat++ cat++.c)
add_library(rot13 SHARED rot13.c)
add_library(upper SHARED upper.c)
add_library(lower SHARED lower.c)
find_library(DL dl)
target_link_libraries(cat++ ${DL})
