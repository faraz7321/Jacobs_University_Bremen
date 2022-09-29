# 
# semaphore/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(SEM C) 
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(Threads REQUIRED)

add_executable(sem-test sem-test.c sem.c)
target_link_libraries(sem-test ${CMAKE_THREAD_LIBS_INIT})
