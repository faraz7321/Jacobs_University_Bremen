/*
 * rad/peer.h --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#ifndef _PEER_H
#define _PEER_H

#include <event2/event.h>

#include "request.h"

typedef struct peer {
    int fd;			/* socket to the peer */
    struct rad *rad;		/* the rad this peer belongs to */
    struct peer *next;		/* next peer in rad's list of peers */
    struct event *ev;		/* event for receiving msgs */
    request_t *request;		/* pending request (if any) */
} peer_t;

extern peer_t *peer_new(struct rad *rad, int fd);
extern void peer_del(peer_t *peer);

extern void peer_send_request(peer_t *peer, request_t *request);
extern void peer_send_reply(peer_t *peer, request_t *request);

#endif
