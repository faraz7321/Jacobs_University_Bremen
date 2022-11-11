# 
# msh/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(MSH C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(msh msh.c msh-util.c)
add_executable(msh-redirect msh-redirect.c msh-util.c)

