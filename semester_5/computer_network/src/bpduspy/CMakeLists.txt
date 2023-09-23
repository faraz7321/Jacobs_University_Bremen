# 
# bpduspy/CMakeLists.txt --
#

cmake_minimum_required(VERSION 2.6)
project(BPDUSPY C) 
add_executable(bpduspy bpduspy.c)
target_link_libraries(bpduspy pcap)
set_property(SOURCE bpduspy.c
             APPEND PROPERTY COMPILE_FLAGS "--std=c99 -Wall")
