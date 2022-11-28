# 
# expect/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(EXPECT C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(PkgConfig REQUIRED)
pkg_check_modules(READLINE readline)
if(NOT READLINE_FOUND)
  # Some Debian installations have readline but no package config
  # file, hopefully this hack can be removed at some point in time.
  SET(READLINE_LDFLAGS "-lreadline")
endif()

add_executable(expect expect.c)
target_link_libraries(expect ${READLINE_LDFLAGS})
target_include_directories(expect PUBLIC ${READLINE_INCLUDE_DIRS})
target_compile_options(expect PUBLIC ${READLINE_CFLAGS_OTHER})
