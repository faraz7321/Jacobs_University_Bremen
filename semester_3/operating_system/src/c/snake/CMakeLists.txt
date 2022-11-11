# 
# snake/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(SNAKE C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(snake main.c snake.c dlist.c)
target_link_libraries(snake ${CURSES_LIBRARIES})
