/*
 * socket/lib/udp-chat.c --
 *
 *	Chat with a UDP server, reading stdin / writing stdout.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "udp.h"

int udp_chat(int fd)
{
    const int maxfd = (fd > STDIN_FILENO ? fd : STDIN_FILENO);
    int rc;
    fd_set fdset;
    
    while (1) {
        FD_ZERO(&fdset);
        FD_SET(STDIN_FILENO, &fdset);
        FD_SET(fd, &fdset);
        if (select(1 + maxfd, &fdset, NULL, NULL, NULL) == -1) {
            perror("select");
            return -1;
        }
	
        if (FD_ISSET(fd, &fdset)) {
            rc = udp_recv_write(fd, STDOUT_FILENO);
            if (rc <= 0) {
                return rc;
            }
        }
	
        if (FD_ISSET(STDIN_FILENO, &fdset)) {
            rc = udp_read_send(STDIN_FILENO, fd);
            if (rc <= 0) {
                return rc;
            }
        }
    }
    
    return 0;
}
