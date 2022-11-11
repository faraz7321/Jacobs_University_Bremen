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

static void usage(FILE *stream, int status)
{
    (void) fprintf(stream, "usage: chatd port\n");
    exit(status);
}

int main(int argc, char *argv[])
{
    int fd, i;
    struct event_base *evb;
    struct event *ev;
    const char *interfaces[] = { "0.0.0.0", "::", NULL };
    
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
    for (i = 0; interfaces[i]; i++) {
        fd = tcp_listen(interfaces[i], argv[1]);
        if (fd == -1) {
	    continue;
	}
	ev = event_new(evb, fd, EV_READ|EV_PERSIST, clnt_join, evb);
	event_add(ev, NULL);
    }
    if (event_base_loop(evb, 0) == -1) {
        fprintf(stderr, "event_base_loop: failed\n");
        event_base_free(evb);
        return EXIT_FAILURE;
    }
    (void) event_base_free(evb);
    (void) tcp_close(fd);
    return EXIT_SUCCESS;
}
