/*
 * socket/examples/httpget.c --
 *
 *      Send an old-style HTTP GET request to a server and read the
 *      response message.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>

#include "tcp.h"

#define HOST    "www.google.com"
#define HTTP    "http"
#define QUERY   "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n"

int main(void)
{
    int sd, rc;
    char buffer[1024];
    
    sd  = tcp_connect(HOST, HTTP);
    if (sd == -1) {
        return EXIT_FAILURE;
    }

    rc = tcp_write(sd, QUERY, strlen(QUERY));
    if (rc == -1) {
        (void) close(sd);
        perror("tcp_write");
        return EXIT_FAILURE;
    }

    shutdown(sd, SHUT_WR);

    while (1) {
        rc = tcp_read(sd, buffer, sizeof(buffer));
        if (rc == -1) {
            perror("tcp_read");
            break;
        }
        if (rc == 0) {
            break;
        }
        (void) printf("%.*s", rc, buffer);
    }

    (void) tcp_close(sd);

    return EXIT_SUCCESS;
}
