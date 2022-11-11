/*
 * rad/peer.c --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "tcp.h"
#include "peer.h"
#include "rad.h"

extern int debug;
extern char *progname;

static void
peer_recv_message(evutil_socket_t evfd, short evwhat, void *evarg)
{
    char buf[128];
    int len;
    peer_t *p = (peer_t *) evarg;
    char type;
    int id;
    unsigned time;

    (void) evfd;
    (void) evwhat;
    assert(p && p->rad && p->fd > 0);

    len = read(p->fd, buf, sizeof(buf));
    if (len == -1 || len == 0) {
	rad_del_peer(p->rad, p);
	peer_del(p);
	return;
    }

    /* parse the received message and notify that rad instance */

    if (sscanf(buf, "%c: <%d, %u>", &type, &id, &time) == 3) {
	switch (type) {
	case 'Q':
	case 'q':
	    rad_recv_request(p->rad, p, id, time);
	    break;
	case 'R':
	case 'r':
	    rad_recv_reply(p->rad, p, id, time);
	    break;
	default:
	    if (debug) {
		fprintf(stderr, "** rad: received unknown message\n");
	    }
	    break;
	}
    }
}

peer_t*
peer_new(rad_t *rad, int fd)
{
    peer_t *p;

    assert(rad && fd);
    
    p = (peer_t *) malloc(sizeof(peer_t));
    if (! p) {
	fprintf(stderr, "%s: out of memory - aborting\n", progname);
	exit(EXIT_FAILURE);
    }
    memset(p, 0, sizeof(peer_t));
    p->fd = fd;
    p->rad = rad;
    
    p->ev = event_new(p->rad->evb, p->fd, EV_READ|EV_PERSIST,
		      peer_recv_message, p);
    event_add(p->ev, NULL);
    
    if (debug) {
	fprintf(stderr, "** peer: new (fd = %d)\n", p->fd);
    }
    return p;
}

void
peer_save_request(peer_t *peer, request_t *request)
{
    assert(peer && request);

    peer->request = request;
}

void
peer_del(peer_t *peer)
{
    assert(peer);

    event_del(peer->ev);
    (void) tcp_close(peer->fd);
    if (peer->request) {
	request_del(peer->request);
    }
    if (debug) {
	fprintf(stderr, "** peer: del (fd = %d)\n", peer->fd);
    }
}

void
peer_send_request(peer_t *peer, request_t *request)
{
    char msg[80];
    size_t msglen;

    assert(peer && peer->rad);
    
    (void) snprintf(msg, sizeof(msg),
		    "Q: <%d, %u>", request->id, request->time);
    msglen = strlen(msg);

    (void) write(peer->fd, msg, msglen);
}

void
peer_send_reply(peer_t *peer, request_t *request)
{
    char msg[80];
    size_t msglen;

    assert(peer && request);
    
    (void) snprintf(msg, sizeof(msg),
		    "R: <%d, %u>", request->id, request->time);
    msglen = strlen(msg);

    (void) write(peer->fd, msg, msglen);
}

