/*
 * socket/lib/tcp-read-write.c --
 *
 *      Copy data from a source a destination file descriptor using
 *      tcp_read() and tcp_write().
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <unistd.h>

#include "tcp.h"

int tcp_read_write(int sfd, int dfd)
{
    char buf[1024];
    int len, rc;

    len = tcp_read(sfd, buf, sizeof(buf));
    if (len <= 0) {
        return len;
    }
    rc = tcp_write(dfd, buf, len);
    return rc;
}
