# 
# pthread/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(ECHO C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(Threads REQUIRED)

add_executable(echo echo.c)
add_executable(echo-fork echo-fork.c)
add_executable(echo-pthread echo-pthread.c)
if(NOT ${APPLE})
  add_executable(echo-pthread-sem echo-pthread-sem.c)
endif()
add_executable(echo-pthread-mutex echo-pthread-mutex.c)
target_link_libraries(echo-pthread ${CMAKE_THREAD_LIBS_INIT})
if(NOT ${APPLE})
  target_link_libraries(echo-pthread-sem ${CMAKE_THREAD_LIBS_INIT})
endif()
target_link_libraries(echo-pthread-mutex ${CMAKE_THREAD_LIBS_INIT})
