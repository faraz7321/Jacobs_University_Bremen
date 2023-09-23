# 
# traceroute/CMakeLists.txt --
#

cmake_minimum_required(VERSION 2.6)
project(TRACEROUTE C) 
add_executable(traceroute traceroute.c)
set_property(SOURCE traceroute.c
             APPEND PROPERTY COMPILE_FLAGS "--std=c99 -Wall")
