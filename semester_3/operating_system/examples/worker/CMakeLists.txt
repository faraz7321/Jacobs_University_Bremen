# 
# worker/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(WORKER C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(Threads REQUIRED)

add_executable(worker worker.c)
target_link_libraries(worker ${CMAKE_THREAD_LIBS_INIT})

