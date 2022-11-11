/*
 * socket/lib/tcp-accept.c --
 *
 *      Accept a pending connection return a new file descriptor for
 *      the new connection.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdlib.h>
#include <sys/socket.h>

#include "tcp.h"

int tcp_accept(int fd)
{
    return accept(fd, NULL, NULL);
}
