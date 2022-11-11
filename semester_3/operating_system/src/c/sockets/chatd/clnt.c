/*
 * socket/chatd/clnt.c --
 *
 *	Creation and deletion of clients, providing a broadcast API.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <event2/event.h>

#include "tcp.h"
#include "clnt.h"

static clnt_t *clients = NULL;

clnt_t* clnt_new()
{
    clnt_t *clnt;
    
    clnt = calloc(1, sizeof(clnt_t));
    if (! clnt) {
	perror("calloc");
	return NULL;
    }
    clnt->next = clients;
    clients = clnt;
    return clnt;
}

void clnt_del(clnt_t *me)
{
    clnt_t *clnt;
    int cfd = me->fd;
    
    event_del(me->event);
    (void) tcp_close(me->fd);
    if (me == clients) {
	clients = me->next;
	(void) free(me);
    } else {
	for (clnt = clients; clnt && clnt->next != me; clnt = clnt->next) ;
	if (clnt->next == me) {
	    clnt->next = me->next;
	    (void) free(me);
	}
    }
    clnt_bcast("server: clnt-%d left\n", cfd);
}

void clnt_bcast(const char *format, ...)
{
    va_list ap;
    char buf[1024];
    int len, rc;
    clnt_t *clnt, *gone = NULL;

    va_start(ap, format);
    len = vsnprintf(buf, sizeof(buf), format, ap);
    if (len > 0) {
	for (clnt = clients; clnt; clnt = clnt->next) {
	    rc = tcp_write(clnt->fd, buf, len);
	    if (rc <= 0) gone = clnt;
	}
    }
    if (gone) clnt_del(gone);
}
