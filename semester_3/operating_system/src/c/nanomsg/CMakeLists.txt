# 
# nanomsg/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(pipeline C) 
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(PkgConfig)
pkg_check_modules(LIBNANOMSG REQUIRED libnanomsg)
include_directories(${LIBNANOMSG_INCLUDE_DIRS})
link_directories(${LIBNANOMSG_LIBRARY_DIRS})

add_executable(pipeline pipeline.c)
target_link_libraries(pipeline ${LIBNANOMSG_LIBRARIES})

add_executable(reqrep reqrep.c)
target_link_libraries(reqrep ${LIBNANOMSG_LIBRARIES})

add_executable(pubsub pubsub.c)
target_link_libraries(pubsub ${LIBNANOMSG_LIBRARIES})
