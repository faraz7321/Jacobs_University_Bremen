/*
 * socket/lib/udp-recv-write.c --
 *
 *	Receive a datagram and write data to a file descriptor.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

#include "udp.h"

int udp_recv_write(int sfd, int dfd)
{
    char buf[1024];
    ssize_t len;
    int rc;

    len = recv(sfd, buf, sizeof(buf), 0);
    if (len == -1) {
	perror("recv");
        return -1;
    }
    if (len == 0) {
        return 0;
    }
    rc = write(dfd, buf, len);
    if (rc == -1) {
        perror("write");
        return -1;
    }
    return rc;
}
