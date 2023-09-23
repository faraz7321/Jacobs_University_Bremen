# 
# pcapdemo/CMakeLists.txt --
#

cmake_minimum_required(VERSION 2.6)
project(PCAPDEMO C) 
add_executable(pcapdemo pcapdemo.c)
target_link_libraries(pcapdemo pcap)
set_property(SOURCE pcapdemo.c
             APPEND PROPERTY COMPILE_FLAGS "--std=c99 -Wall")
