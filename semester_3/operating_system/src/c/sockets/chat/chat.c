/*
 * socket/chat/chat.c --
 *
 *      A basic chat program sending messages read from standard input
 *      to a server and printing messages received from a server.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tcp.h"
#include "udp.h"

#define USE_TCP  0x1
#define USE_UDP  0x2

static void usage(FILE *stream, int status)
{
    (void) fprintf(stream, "usage: chat host port\n");
    exit(status);
}

int main(int argc, char *argv[])
{
    int c, fd, use = USE_TCP;

    while ((c = getopt(argc, argv, "ut")) != -1) {
        switch (c) {
        case 'u':
            use = USE_UDP;
            break;
        case 't':
            use = USE_TCP;
            break;
        case '?':
        default:
            usage(stdout, EXIT_SUCCESS);
        }
    }
    argc -= optind;
    argv += optind;

    if (argc != 2) {
        usage(stderr, EXIT_FAILURE);
    }

    if (use == USE_TCP) {
        if ((fd = tcp_connect(argv[0], argv[1])) == -1) {
            return EXIT_FAILURE;
        }
        if (tcp_chat(fd) == -1) {
            (void) tcp_close(fd);
            return EXIT_FAILURE;
        }
        (void) tcp_close(fd);
    }
    if (use == USE_UDP) {
        if ((fd = udp_connect(argv[0], argv[1])) == -1) {
            return EXIT_FAILURE;
        }
        if (udp_chat(fd) == -1) {
            (void) udp_close(fd);
            return EXIT_FAILURE;
        }
        (void) udp_close(fd);
    }
    return EXIT_SUCCESS;
}
