/*
 * rad/rad.c --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <time.h>

#include <event2/event.h>

#include "tcp.h"
#include "peer.h"
#include "rad.h"

extern int debug;
extern char *progname;

void
rad_enter_critical(rad_t *rad)
{
    peer_t *p;
    unsigned t;

    rad_set_state(rad, RAD_STATE_ENTER);

    t = time(NULL);
    assert(t);
    rad->request = request_new(rad->id, t);

    for (p = rad->peers, rad->missing = 0; p; p = p->next) {
	peer_send_request(p, rad->request);
	rad->missing++;
    }

    /* we now wait for rad->missing to become 0 again */
}

void
rad_leave_critical(rad_t *rad)
{
    peer_t *p;
    
    rad_set_state(rad, RAD_STATE_LEAVE);

    /* send a reply to all peers with pending requests */

    for (p = rad->peers; p; p = p->next) {
	if (p->request) {
	    peer_send_reply(p, p->request);
	    request_del(p->request);
	    p->request = NULL;
	}
    }

    rad_set_state(rad, RAD_STATE_CONNECTED);
}

static void
rad_tick(evutil_socket_t evfd, short evwhat, void *evarg)
{
    rad_t *rad = (rad_t *) evarg;

    (void) evfd;
    (void) evwhat;
    assert(rad);

    rad->ticks++;

    switch (rad->state) {
    case RAD_STATE_CONNECTED:
	if (rad->ticks >= 5) {
	    rad_enter_critical(rad);
	}
	break;
    case RAD_STATE_CRITICAL:
	if (rad->ticks >= 2) {
	    rad_leave_critical(rad);
	}
    default:
	break;
    }
}

static void
rad_accept_peer(evutil_socket_t evfd, short evwhat, void *evarg)
{
    int cfd;
    peer_t *p;
    rad_t *rad = (rad_t *) evarg;

    (void) evfd;
    (void) evwhat;

    assert(rad && rad->fd > 0);
    
    cfd = tcp_accept(rad->fd);
    if (cfd == -1) {
        return;
    }

    p = peer_new(rad, cfd);
    rad_add_peer(rad, p);
}

rad_t*
rad_new(struct event_base *evb, int id, int fd, int num)
{
    rad_t *rad;
    struct timeval one_second = { 1, 0 };
    
    rad = (rad_t *) malloc(sizeof(rad_t));
    if (! rad) {
	fprintf(stderr, "%s: out of memory - aborting\n", progname);
	exit(EXIT_FAILURE);
    }
    memset(rad, 0, sizeof(rad_t));
    rad->id = id;
    rad->evb = evb;
    rad->fd = fd;
    rad->num = num;
    rad_set_state(rad, RAD_STATE_WAITING);

    rad->ev = event_new(rad->evb, rad->fd, EV_READ|EV_PERSIST,
			rad_accept_peer, rad);
    event_add(rad->ev, NULL);

    rad->tev = event_new(rad->evb, 0, EV_TIMEOUT|EV_PERSIST,
			 rad_tick, rad);
    event_add(rad->tev, &one_second);
    

    if (debug) {
	fprintf(stderr, "** rad: new, id = %d\n", rad->id);
    }
    return rad;
}

void
rad_del(rad_t *rad)
{
    assert(rad);

    /* xxx */

    event_del(rad->ev);
    event_del(rad->tev);
    if (rad->request) {
	request_del(rad->request);
    }
    (void) free(rad);
    
    if (debug) {
	fprintf(stderr, "** rad: del\n");
    }
}

void
rad_set_state(rad_t *rad, int state)
{
    assert(rad);
    char *rad_states[] = {
	"unknown",
	"waiting",
	"connected",
	"enter",
	"critical",
	"leave"
    };

    rad->state = state;
    rad->ticks = 0;

    if (debug) {
	if (state >= 0 && state < (int) (sizeof(rad_states)/sizeof(rad_states[0]))) {
	    fprintf(stderr, "** rad: new state %s\n",
		    rad_states[rad->state]);
	} else {
	    fprintf(stderr, "** rad: new state %d\n", rad->state);
	}
    }
}

void
rad_add_peer(rad_t *rad, peer_t *peer)
{
    assert(rad);
    
    peer->next = rad->peers;
    rad->peers = peer;

    if (rad_len_peers(rad) + 1 == rad->num) {
	rad_set_state(rad, RAD_STATE_CONNECTED);
    }
}

void
rad_del_peer(rad_t *rad, peer_t *peer)
{
    peer_t *p, *last;
    
    assert(rad);

    for (p = rad->peers, last = NULL; p != peer; last = p, p = p->next) {
    }
    if (p) {
	if (last) {
	    last->next = p->next;
	} else {
	    rad->peers = p->next;
	}
    }
    p->next = NULL;
    p->rad = NULL;

    if (rad_len_peers(rad) + 1 < rad->num) {
	rad_set_state(rad, RAD_STATE_WAITING);
    }
}

int
rad_len_peers(rad_t *rad)
{
    int cnt = 0;
    peer_t *p;

    assert(rad);
    
    for (p = rad->peers; p; p = p->next) {
	cnt++;
    }
    return cnt;
}

void rad_recv_request(rad_t *rad, peer_t *peer, int id, unsigned int time)
{
    request_t *request;
    int cmp;
    
    assert(rad);

    request = request_new(id, time);

    switch (rad->state) {
    case RAD_STATE_CONNECTED:
	peer_send_reply(peer, request);
	request_del(request);
	break;
    case RAD_STATE_ENTER:
	cmp = request_cmp(request, rad->request);
	if (cmp < 0) {
	    peer_send_reply(peer, request);
	    request_del(request);
	} else if (cmp > 0) {
	    peer->request = request;
	    if (debug) {
		fprintf(stderr, "** rad: queuing request with larger timestamp\n");
	    }
	} else {
	    if (debug) {
		fprintf(stderr, "** rad: ignoring request with same timestamp\n");
	    }
	    request_del(request);
	}
	break;
    case RAD_STATE_CRITICAL:
    case RAD_STATE_LEAVE:
	peer->request = request;
	if (debug) {
	    fprintf(stderr, "** rad: queuing request while being critical\n");
	}
	break;
    default:
	request_del(request);
	if (debug) {
	    fprintf(stderr, "** rad: received unexpected request\n");
	}
    }
}

void rad_recv_reply(rad_t *rad, peer_t *peer, int id, unsigned int time)
{
    (void) peer;
    (void) id;
    (void) time;
    assert(rad);

    switch (rad->state) {
    case RAD_STATE_ENTER:
	rad->missing--;
	if (rad->missing == 0) {
	    request_del(rad->request);
	    rad->request = NULL;
	    rad_set_state(rad, RAD_STATE_CRITICAL);
	}
	break;
    default:
	if (debug) {
	    fprintf(stderr, "** rad: received unexpected reply\n");
	}
	break;
    }
}
