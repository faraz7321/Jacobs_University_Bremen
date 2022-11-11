/*
 * socket/lib/tcp-chat.c --
 *
 *	Chat with a TCP server, reading stdin / writing stdout.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>

#include "tcp.h"

int tcp_chat(int fd)
{
    const int maxfd = (fd > STDIN_FILENO ? fd : STDIN_FILENO);
    int rc;
    fd_set fdset;
    
    (void) fcntl(fd, F_SETFL, O_NONBLOCK);
    (void) fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    while (1) {
        FD_ZERO(&fdset);
        FD_SET(STDIN_FILENO, &fdset);
        FD_SET(fd, &fdset);
        if (select(1 + maxfd, &fdset, NULL, NULL, NULL) == -1) {
            perror("select");
            return -1;
        }
	
        if (FD_ISSET(fd, &fdset)) {
            rc = tcp_read_write(fd, STDOUT_FILENO);
            if (rc <= 0) {
                return rc;
            }
        }
	
        if (FD_ISSET(STDIN_FILENO, &fdset)) {
            rc = tcp_read_write(STDIN_FILENO, fd);
            if (rc <= 0) {
                return rc;
            }
        }
    }
    
    return 0;
}
