# 
# wlanspy/CMakeLists.txt --
#

cmake_minimum_required(VERSION 2.6)
project(WLANSPY C) 
add_executable(wlanspy wlanspy.c)
target_link_libraries(wlanspy pcap)
set_property(SOURCE wlanspy.c
             APPEND PROPERTY COMPILE_FLAGS "--std=c99 -Wall")
