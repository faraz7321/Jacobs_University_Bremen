/*
 * rad/rad.h --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#ifndef _RAD_H
#define _RAD_H

#include <event2/event.h>

#include "request.h"
#include "peer.h"

typedef enum rad_state {
    RAD_STATE_WAITING = 1,
    RAD_STATE_CONNECTED = 2,
    RAD_STATE_ENTER = 3,
    RAD_STATE_CRITICAL = 4,
    RAD_STATE_LEAVE = 5
} rad_state_t;

typedef struct rad {
    int id;			/* a better unique id */
    int fd;			/* listening socket */
    int num;			/* number of peers to connect */
    rad_state_t state;		/* state of the rad (see above) */
    int missing;		/* # of missing replies */
    int ticks;			/* number of ticks in current state */
    request_t *request;		/* active request (if any) */
    peer_t *peers;		/* peers connected to the rad */
    struct event *ev;		/* event for incoming connections */
    struct event *tev;		/* event for periodic timers */
    struct event_base *evb;	/* event base used by the rad */
} rad_t;

extern rad_t* rad_new(struct event_base *evb, int id, int fd, int num);
extern void rad_del(rad_t *rad);

extern void rad_set_state(rad_t *rad, int state);
extern void rad_add_peer(rad_t *rad, peer_t *peer);
extern void rad_del_peer(rad_t *rad, peer_t *peer);
extern int  rad_len_peers(rad_t *rad);

extern void rad_enter_critical(rad_t *rad);
extern void rad_leave_critical(rad_t *rad);

extern void rad_recv_request(rad_t *rad, peer_t *peer,
			     int id, unsigned int time);
extern void rad_recv_reply(rad_t *rad, peer_t *peer,
			   int id, unsigned int time);

#endif
