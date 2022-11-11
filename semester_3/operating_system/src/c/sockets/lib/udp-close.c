/*
 * socket/lib/udp-close.c --
 *
 *	Close a UDP socket. On a POSIX system, we simply call the
 *      close() system call.
 */

#define _POSIX_C_SOURCE 201112L

#include <unistd.h>

#include "udp.h"

int udp_close(int fd)
{
    return close(fd);
}
