# 
# gsh/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(GSH C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
add_definitions(${GLIB2_CFLAGS})

add_executable(gsh gsh.c)
target_link_libraries(gsh ${GLIB2_LDFLAGS})
