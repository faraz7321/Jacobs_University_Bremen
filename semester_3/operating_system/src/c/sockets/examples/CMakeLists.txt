# 
# sockets/examples/CMakeLists.txt --
#

find_package(Threads REQUIRED)

add_executable(showip showip.c)
add_executable(httpget httpget.c)
add_executable(echod echod.c)

target_link_libraries(httpget LINK_PUBLIC libtcp)
target_link_libraries(echod LINK_PUBLIC libtcp ${CMAKE_THREAD_LIBS_INIT})
