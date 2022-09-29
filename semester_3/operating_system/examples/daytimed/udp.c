/*
 * daytimed/udp.c --
 *
 * A couple of wrapper functions for simple TCP server applications.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <syslog.h>

/*
 * Create a named UDP endpoint. First get the list of potential
 * network layer addresses and transport layer port numbers. Iterate
 * through the returned address list until an attempt to create a UDP
 * endpoint is successful (or no other alternative exists).
 */

int
udp_open(const char *host, const char *port)
{
    struct addrinfo hints, *ai_list, *ai;
    int n, fd = 0, on = 1;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    n = getaddrinfo(host, port, &hints, &ai_list);
    if (n) {
        syslog(LOG_ERR, "getaddrinfo failed: %s", gai_strerror(n));
        return -1;
    }

    for (ai = ai_list; ai; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd < 0) {
            continue;
        }

#ifdef IPV6_V6ONLY
        /*
         * Some IPv6 stacks by default accept IPv4-mapped addresses on
	 * IPv6 sockets and hence binding a port separately for both
	 * IPv4 and IPv6 sockets fails on these systems by default.
	 * This can be avoided by making the IPv6 socket explicitly an
	 * IPv6 only socket.
         */
        if (ai->ai_family == AF_INET6) {
            (void) setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));
        }
#endif

        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(fd, ai->ai_addr, ai->ai_addrlen) == 0) {
            break;
        }
        close(fd);
    }

    freeaddrinfo(ai_list);

    if (ai == NULL) {
        syslog(LOG_ERR, "bind failed for port %s", port);
        return -1;
    }

    return fd;
}

/*
 * Close a udp socket. This function trivially calls close() on
 * POSIX systems, but might be more complicated on other systems.
 */

int
udp_close(int fd)
{
    return close(fd);
}

