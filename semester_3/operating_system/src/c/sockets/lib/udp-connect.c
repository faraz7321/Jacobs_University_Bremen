/*
 * socket/lib/udp-connect.c --
 *
 *      Create a UDP socket and "connect" it to a remote server.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "udp.h"

int udp_connect(const char *host, const char *port)
{
    struct addrinfo hints, *ai_list, *ai;
    int rc, fd = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    rc = getaddrinfo(host, port, &hints, &ai_list);
    if (rc != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
        return -1;
    }
    for (ai = ai_list; ai; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd < 0) {
            switch (errno) {
            case EAFNOSUPPORT:
            case EPROTONOSUPPORT:
                continue;
            default:
                perror("socket");
                continue;
            }
        } else {
            if (connect(fd, ai->ai_addr, ai->ai_addrlen) == -1) {
                (void) close(fd);
                perror("connect");
                continue;
            }
        }
        break;  /* we were successful, break out of the loop */
    }
    freeaddrinfo(ai_list);
    if (ai == NULL) {
        fprintf(stderr, "failed to connect to '%s' port '%s'\n", host, port);
        return -1;
    }
    return fd;
}
