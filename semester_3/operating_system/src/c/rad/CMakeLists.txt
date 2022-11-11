# 
# rad/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(RAD C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVENT REQUIRED libevent)
include_directories(${LIBEVENT_INCLUDE_DIRS})
link_directories(${LIBEVENT_LIBRARY_DIRS})

add_executable(rad request.c peer.c tcp.c rad.c main.c)
target_link_libraries(rad ${LIBEVENT_LIBRARIES})
