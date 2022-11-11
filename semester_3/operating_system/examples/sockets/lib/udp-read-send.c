/*
 * socket/lib/udp-read-send.c --
 *
 *	Read data from a file descriptor and send it as a datagram.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

#include "udp.h"

int udp_read_send(int sfd, int dfd)
{
    char buf[1024];
    int len, rc;

    len = read(sfd, buf, sizeof(buf));
    if (len == -1) {
        perror("read");
	return -1;
    }
    if (len == 0) {
        return 0;
    }
    rc = send(dfd, buf, len, 0);
    if (rc == -1) {
	perror("send");
	return -1;
    }
    return rc;
}
