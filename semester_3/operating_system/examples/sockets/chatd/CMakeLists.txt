#
# sockets/chatd/CMakeLists.txt --
#

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVENT REQUIRED libevent)
include_directories(${LIBEVENT_INCLUDE_DIRS})
link_directories(${LIBEVENT_LIBRARY_DIRS})

add_executable(chatd chatd.c clnt.c clnt-event.c)

target_link_libraries(chatd LINK_PUBLIC libtcp libudp ${LIBEVENT_LIBRARIES})
