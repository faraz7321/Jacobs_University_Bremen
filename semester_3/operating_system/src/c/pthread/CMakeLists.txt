# 
# pthread/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)

project(PTHREAD C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
find_package(Threads REQUIRED)

add_executable(pthread pthread.c)
add_executable(pthread-mutex pthread-mutex.c)
add_executable(pthread-cond pthread-cond.c)
add_executable(pthread-rwlock pthread-rwlock.c)
add_executable(pthread-multiplex pthread-multiplex.c)
if(NOT ${APPLE})
  add_executable(pthread-barrier pthread-barrier.c)
  add_executable(pthread-sem pthread-sem.c)
endif()
add_executable(pthread-fib pthread-fib.c)
add_executable(pthread-fork pthread-fork.c)

target_link_libraries(pthread ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pthread-mutex ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pthread-cond ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pthread-rwlock ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pthread-multiplex ${CMAKE_THREAD_LIBS_INIT})
if(NOT ${APPLE})
  target_link_libraries(pthread-barrier ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(pthread-sem ${CMAKE_THREAD_LIBS_INIT})
endif()
target_link_libraries(pthread-fib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pthread-fork ${CMAKE_THREAD_LIBS_INIT})

