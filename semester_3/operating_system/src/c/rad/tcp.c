/*
 * rad/tcp.c --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

extern char *progname;

#include "tcp.h"

/*
 * Establish a connection to a remote TCP server. First get the list
 * of potential network layer addresses and transport layer port
 * numbers. Iterate through the returned address list until an attempt
 * to establish a TCP connection is successful (or no other
 * alternative exists).
 */

int
tcp_connect(char *host, char *port)
{
    struct addrinfo hints, *ai_list, *ai;
    int n, fd = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    n = getaddrinfo(host, port, &hints, &ai_list);
    if (n != 0) {
        fprintf(stderr, "%s: getaddrinfo: %s\n",
		progname, gai_strerror(n));
        exit(EXIT_FAILURE);
    }

    for (ai = ai_list; ai; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd < 0) {
	    switch (errno) {
	    case EAFNOSUPPORT:
	    case EPROTONOSUPPORT:
		continue;
		
	    default:
		fprintf(stderr, "%s: socket: %s\n",
			progname, strerror(errno));
		continue;
	    }
        } else {
	    if (connect(fd, ai->ai_addr, ai->ai_addrlen) == -1) {
		close(fd);
		fprintf(stderr, "%s: connect: %s\n",
			progname, strerror(errno));
		continue;
	    }
        }
	break;	/* still here? we were successful and we are done */
    }

    freeaddrinfo(ai_list);

    if (ai == NULL) {
        fprintf(stderr, "%s: could not connect to %s port %s\n",
                progname, host, port);
        exit(EXIT_FAILURE);
    }

    return fd;
}

/*
 * Create a listening TCP endpoint. First get the list of potential
 * network layter addresses and transport layer port numbers. Iterate
 * through the returned address list until an attempt to create a
 * listening TCP endpoint is successful (or no other alternative
 * exists).
 */

int
tcp_listen(char *port)
{
    struct addrinfo hints, *ai_list, *ai;
    int n, fd = 0, on = 1;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    n = getaddrinfo(NULL, port, &hints, &ai_list);
    if (n) {
        fprintf(stderr, "%s: getaddrinfo failed: %s\n",
                progname, gai_strerror(n));
        return -1;
    }

    for (ai = ai_list; ai; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd < 0) {
            continue;
        }

        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(fd, ai->ai_addr, ai->ai_addrlen) == 0) {
            break;
        }
        close(fd);
    }

    freeaddrinfo(ai_list);

    if (ai == NULL) {
        fprintf(stderr, "%s: bind failed for port %s\n",
                progname, port);
        return -1;
    }

    if (listen(fd, 42) < 0) {
        fprintf(stderr, "%s: listen failed: %s\n",
                progname, strerror(errno));
        return -1;
    }

    return fd;
}

/*
 * Accept a new TCP connection and write a message about who was
 * accepted to the system log.
 */

int
tcp_accept(int listen)
{
    return accept(listen, NULL, 0);
}

/*
 * Close a TCP connection. This function trivially calls close() on
 * POSIX systems, but might be more complicated on other systems.
 */

int
tcp_close(int fd)
{
    return close(fd);
}

