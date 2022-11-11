/*
 * rad/request.c --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "request.h"

extern int debug;
extern char *progname;


request_t*
request_new(int id, unsigned time)
{
    request_t *request;

    request = (request_t *) malloc(sizeof(request_t));
    if (! request) {
	fprintf(stderr, "%s: out of memory - aborting\n", progname);
	exit(EXIT_FAILURE);
    }
    memset(request, 0, sizeof(request_t));
    request->id = id;
    request->time = time;

    if (debug) {
	fprintf(stderr, "** request: new (id = %d, time = %u)\n",
		request->id, request->time);
    }
    return request;
}

void
request_del(request_t *request)
{
    if (debug) {
	fprintf(stderr, "** request: del (id = %d, time = %u)\n",
		request->id, request->time);
    }
    (void) free(request);
}

int
request_cmp(request_t *a, request_t *b)
{
    assert(a && b);

    if (a->time == b->time && a->id == b->id) {
	return 0;
    }

    if (a->time < b->time || (a->time == b->time && a->id < b->id)) {
	return -1;
    } else {
	return 1;
    }
}
