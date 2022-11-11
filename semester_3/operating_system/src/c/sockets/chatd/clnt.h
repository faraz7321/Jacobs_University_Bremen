/*
 * socket/clnt.h --
 *
 */

#ifndef _CLNT_H
#define _CLNT_H

#include <event2/event.h>

typedef struct clnt {
    evutil_socket_t   fd;
    struct event      *event;
    struct clnt       *next;
} clnt_t;

clnt_t* clnt_new();
void clnt_del(clnt_t *clnt);
void clnt_bcast(const char *format, ...);

void clnt_join(evutil_socket_t evfd, short evwhat, void *evarg);
void clnt_read(evutil_socket_t evfd, short evwhat, void *evarg);

#endif
