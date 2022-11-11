# 
# sockets/lib/CMakeLists.txt --
#

add_library(libtcp tcp-connect.c tcp-listen.c tcp-accept.c tcp-read.c tcp-write.c tcp-read-write.c tcp-chat.c tcp-close.c)
add_library(libudp udp-connect.c udp-socket.c udp-recv-write.c udp-read-send.c udp-chat.c udp-close.c)

target_include_directories(libtcp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(libudp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
