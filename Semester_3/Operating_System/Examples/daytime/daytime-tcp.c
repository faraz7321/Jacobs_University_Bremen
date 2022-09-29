/*
 * daytime/daytime-tcp.c --
 *
 * A simple TCP over IPv4/IPv6 daytime client.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

static const char *progname = "daytime";

#ifndef NI_MAXHOST
#define NI_MAXHOST	1025
#endif
#ifndef NI_MAXSERV
#define NI_MAXSERV	32
#endif

/*
 * Establish a connection to a remote TCP server. First get the list
 * of potential network layer addresses and transport layer port
 * numbers. Iterate through the returned address list until an attempt
 * to establish a TCP connection is successful (or no other
 * alternative exists).
 */

static int
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
 * Close a TCP connection. This function trivially calls close() on
 * POSIX systems, but might be more complicated on other systems.
 */

static int
tcp_close(int fd)
{
    return close(fd);
}

/*
 * Implement the daytime protocol, loosely modeled after RFC 867.
 */

static void
daytime(int fd)
{
    struct sockaddr_storage peer;
    socklen_t peerlen = sizeof(peer);
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    char message[128], *p;
    ssize_t n;
    
    /* Get the socket address of the remote end and convert it
     * into a human readable string (numeric format). */

    n = getpeername(fd, (struct sockaddr *) &peer, &peerlen);
    if (n) {
        fprintf(stderr, "%s: getpeername: %s\n",
                progname, strerror(errno));
        return;
    }

    n = getnameinfo((struct sockaddr *) &peer, peerlen,
                    host, sizeof(host), serv, sizeof(serv),
                    NI_NUMERICHOST | NI_NUMERICSERV);
    if (n) {
        fprintf(stderr, "%s: getnameinfo: %s\n",
                progname, gai_strerror(n));
        return;
    }

    while ((n = read(fd, message, sizeof(message) - 1)) > 0) {
        message[n] = '\0';
        p = strstr(message, "\r\n");
        if (p) *p = 0;
        printf("%s%s%s:%s\t %s\n",
	       strchr(host, ':') == NULL ? "" : "[",
	       host,
	       strchr(host, ':') == NULL ? "" : "]",
	       serv, message);
    }
}


int
main(int argc, char *argv[])
{
    int fd;

    if (argc != 3) {
        fprintf(stderr, "usage: %s host port\n", progname);
        return EXIT_FAILURE;
    }

    fd = tcp_connect(argv[1], argv[2]);
    daytime(fd);
    tcp_close(fd);
    
    return EXIT_SUCCESS;
}
