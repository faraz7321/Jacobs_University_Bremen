/*
 * socket/chatd/chatd.c --
 *
 *      A basic TCP chat daemon using libevent.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <event2/event.h>

#include "tcp.h"
#include "clnt.h"

typedef struct {
    char *address;
    int fd;
} listen_t;

static void usage(FILE *stream, int status)
{
    (void) fprintf(stream, "usage: chatd port\n");
    exit(status);
}

int main(int argc, char *argv[])
{
    struct event_base *evb;
    struct event *ev;
    listen_t *iface, interfaces[] = {
        { .address = "0.0.0.0" },               /* IPv4 any address */
        { .address = "::" },                    /* IPv6 any address */
        { .address = NULL }                     /* end marker */
    };
    
    if (argc != 2) {
        usage(stderr, EXIT_FAILURE);
    }

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }

    evb = event_base_new();
    if (! evb) {
        fprintf(stderr, "event_base_new: failed\n");
        return EXIT_FAILURE;
    }
    for (iface = interfaces; iface->address; iface++) {
        iface->fd = tcp_listen(iface->address, argv[1]);
        if (iface->fd == -1) {
	    continue;
	}
	ev = event_new(evb, iface->fd, EV_READ|EV_PERSIST, clnt_join, evb);
	event_add(ev, NULL);
    }
    if (event_base_loop(evb, 0) == -1) {
        fprintf(stderr, "event_base_loop: failed\n");
        event_base_free(evb);
        return EXIT_FAILURE;
    }
    (void) event_base_free(evb);
    return EXIT_SUCCESS;
}
