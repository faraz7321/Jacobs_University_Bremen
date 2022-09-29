# 
# daytime/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(DAYTIME C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(daytime-tcp daytime-tcp.c)
add_executable(daytime-udp daytime-udp.c)
