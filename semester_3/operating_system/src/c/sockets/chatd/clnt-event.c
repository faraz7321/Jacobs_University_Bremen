/*
 * socket/chatd/clnt-event.c --
 *
 *	Client related event callbacks.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <event2/event.h>

#include "tcp.h"
#include "clnt.h"

void clnt_read(evutil_socket_t evfd, short evwhat, void *evarg)
{
    char buf[1024];
    int len;
    clnt_t *me = evarg;

    (void) evwhat;

    len = tcp_read(evfd, buf, sizeof(buf));
    if (len <= 0) {
	clnt_del(me);
	return;
    }
    
    clnt_bcast("clnt-%d: %.*s", evfd, len, buf);
}

void clnt_join(evutil_socket_t evfd, short evwhat, void *evarg)
{
    int cfd;
    clnt_t *clnt;
    struct event_base *evb = evarg;

    (void) evwhat;

    cfd = tcp_accept(evfd);
    if (cfd == -1) {
	return;
    }
    (void) fcntl(cfd, F_SETFL, O_NONBLOCK);
    clnt = clnt_new();
    if (! clnt) {
	return;
    }

    clnt->fd = cfd;
    clnt->event = event_new(evb, cfd, EV_READ|EV_PERSIST, clnt_read, clnt);
    (void) event_add(clnt->event, NULL);

    clnt_bcast("server: clnt-%d joined\n", cfd);
}
