# 
# signals/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(SIGNALS C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(alarm alarm.c)
add_executable(catc catc.c)
add_executable(catp catp.c)
add_executable(surprise surprise.c)
