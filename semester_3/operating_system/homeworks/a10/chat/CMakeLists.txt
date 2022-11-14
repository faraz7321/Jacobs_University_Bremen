#
# sockets/chat/CMakeLists.txt --
#

add_executable(chat chat.c)

target_link_libraries(chat LINK_PUBLIC libtcp libudp)
