# 
# pets/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(PETS C) 
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(Threads REQUIRED)

add_executable(pets pets.c)
target_link_libraries(pets ${CMAKE_THREAD_LIBS_INIT})

