# 
# sockets/examples/CMakeLists.txt --
#

add_executable(showip showip.c)
add_executable(httpget httpget.c)

target_link_libraries(httpget LINK_PUBLIC libtcp)
