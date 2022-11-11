# 
# pipe/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(PIPE C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(pipe pipe.c)
add_executable(pipex pipex.c)
add_executable(mail mail.c)
add_executable(pager pager.c)

