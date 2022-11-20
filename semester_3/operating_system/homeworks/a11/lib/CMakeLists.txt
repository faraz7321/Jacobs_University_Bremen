# 
# sockets/lib/CMakeLists.txt --
#

add_library(libtcp tcp-connect.c tcp-listen.c tcp-accept.c tcp-read.c tcp-write.c tcp-read-write.c tcp-chat.c tcp-close.c)

target_include_directories(libtcp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
