# 
# daytimed/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(DAYTIMED C)
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

add_executable(daytimed-tcp daytimed-tcp.c tcp.c)
add_executable(daytimed-udp daytimed-udp.c udp.c)
add_executable(daytimed-tcp-udp daytimed-tcp-udp.c tcp.c udp.c)
add_executable(daytimed-libevent daytimed-libevent.c tcp.c udp.c)
target_link_libraries(daytimed-libevent ${LIBEVENT_LIBRARIES})
