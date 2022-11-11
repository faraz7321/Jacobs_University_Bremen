/*
 * socket/lib/tcp-close.c --
 *
 *      Close the connection to a TCP server. On a POSIX system, we
 *      simply call the close() system call.
 */

#define _POSIX_C_SOURCE 201112L

#include <unistd.h>

#include "tcp.h"

int tcp_close(int fd)
{
    return close(fd);
}
