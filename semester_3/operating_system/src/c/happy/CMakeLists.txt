# 
# happy/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.12)
project(happy C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(happy happy.c)

install(TARGETS happy DESTINATION bin)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
##set(CPACK_DEBIAN_PACKAGE_DEPENDS "cssrobopec")
set(CPACK_PACKAGE_DESCRIPTION "Happy Eyeballs Testing Program")
set(CPACK_PACKAGE_CONTACT "js@beadg.de")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/Debian/postinst")
include(CPack)
