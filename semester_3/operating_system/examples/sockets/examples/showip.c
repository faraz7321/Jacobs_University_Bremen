/*
 * socket/examples/showip.c --
 *
 *      Print the IP addresses for each node name provided on the
 *      command line.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef NI_MAXHOST
#define NI_MAXHOST      1025
#endif
#ifndef NI_MAXSERV
#define NI_MAXSERV      32
#endif

static void showip(char *name)
{
    int rc;
    struct addrinfo hints, *res, *p;
    char host[NI_MAXHOST], serv[NI_MAXSERV];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    rc = getaddrinfo(name, NULL, &hints, &res);
    if (rc) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
        return;
    }
    for (p = res; p; p = p->ai_next) {
        rc = getnameinfo(p->ai_addr, p->ai_addrlen,
                         host, sizeof(host), serv, sizeof(serv),
                         NI_NUMERICHOST | NI_NUMERICSERV);
        if (rc) {
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(rc));
            continue;
        }
        printf("%s\t%s\n", name, host);
    }
    (void) freeaddrinfo(res);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        showip(argv[i]);
    }
    return EXIT_SUCCESS;
}
