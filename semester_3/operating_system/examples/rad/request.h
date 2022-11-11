/*
 * rad/request.h --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#ifndef _REQUEST_H
#define _REQUEST_H

#include <event2/event.h>

typedef struct request {
    int id;			/* the unique id of a peer or 0 */
    unsigned time;		/* the time of the request or 0 */
} request_t;

extern request_t *request_new(int id, unsigned time);
extern void request_del(request_t *request);

extern int request_cmp(request_t *a, request_t *b);

#endif
