/*
 * finger/finger.c --
 *
 *      A simple TCP over IPv4/IPv6 finger client.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

static const char *progname = "finger";

/*
 * Establish a connection to a remote TCP server. First get the list
 * of potential network layer addresses and transport layer port
 * numbers. Iterate through the returned address list until an attempt
 * to establish a TCP connection is successful (or no other
 * alternative exists).
 */

static int
tcp_connect(const char *host, const char *port)
{
    struct addrinfo hints, *ai_list, *ai;
    int n, fd = 0, serrs = 0, cerrs = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    n = getaddrinfo(host, port, &hints, &ai_list);
    if (n) {
        fprintf(stderr, "%s: getaddrinfo: %s\n",
                progname, gai_strerror(n));
        exit(EXIT_FAILURE);
    }

    for (ai = ai_list; ai; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd < 0) {
            serrs++;
            continue;
        }
        if (connect(fd, ai->ai_addr, ai->ai_addrlen) == 0) {
            break;
        }
        cerrs++;
        close(fd);
    }

    freeaddrinfo(ai_list);

    if (ai == NULL) {
        if ((serrs == 1 && ! cerrs) || (!serrs && cerrs == 1)) {
            fprintf(stderr, "%s: %s: %s\n", progname,
                    serrs ? "socket" : "connect", strerror(errno));
        } else {
            fprintf(stderr, "%s: socket or connect: failed for %s port %s\n",
                    progname, host, port);
        }
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
 * Implement the finger protocol, loosely modeled after RFC 1288.
 */

static void
finger(int fd, const char *user, const int lflag)
{
    struct sockaddr_storage peer;
    socklen_t peerlen = sizeof(peer);
    char host[256];
    char message[256];
    ssize_t n;
    
    /* Get the socket address of the remote end and convert it
     * into a human readable string (non-numeric format). */

    n = getpeername(fd, (struct sockaddr *) &peer, &peerlen);
    if (n) {
        fprintf(stderr, "%s: getpeername: %s\n",
                progname, strerror(errno));
        return;
    }

    n = getnameinfo((struct sockaddr *) &peer, peerlen,
                    host, sizeof(host), NULL, 0, 0);
    if (n) {
        fprintf(stderr, "%s: getnameinfo: %s\n",
                progname, gai_strerror(n));
        return;
    }

    /* Implement the finger protocol (see RFC 1288) */

    printf("[%s]\n", host);
    if (lflag) {
        (void) write(fd, "/W ", 3);
    }
    (void) write(fd, user, strlen(user));
    (void) write(fd, "\r\n", 2);

    while ((n = read(fd, message, sizeof(message) - 1)) > 0) {
        (void) write(0, message, n);
    }
}

int
main(int argc, char *argv[])
{
    int i, c, fd;
    char *user, *host;
    int lopt = 0, sopt = 0, lflag;

    while ((c = getopt(argc, argv, "ls")) >= 0) {
        switch (c) {
        case 'l':
            lopt = 1;
            sopt = 0;
            break;
        case 's':
            sopt = 1;
            lopt = 0;
            break;
        }
    }

    if (argc == optind) {
        fprintf(stderr, "usage: %s [-l] [-s] [user]@host ...\n", progname);
        return EXIT_FAILURE;
    }

    for (i = optind; i < argc; i++) {
        if (i > optind) {
            printf("\n");
        }
        user = argv[i];
        host = strrchr(user, '@');
        if (! host) {
            fprintf(stderr, "%s: format must be [user]@host\n", progname);
            continue;
        }
        *host = 0;
        host++;
        lflag = (user[0] != 0);
        if (sopt) lflag = 0;
        if (lopt) lflag = 1;
        fd = tcp_connect(host, "finger");
        finger(fd, user, lflag);
        tcp_close(fd);
    }
    
    return EXIT_SUCCESS;
}
