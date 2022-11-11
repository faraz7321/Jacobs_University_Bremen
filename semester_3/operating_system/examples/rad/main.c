/*
 * rad/main.c --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <time.h>

#include <event2/event.h>

#include "tcp.h"
#include "peer.h"
#include "rad.h"

const char *progname = "rad";
int debug = 0;

int
main(int argc, char *argv[])
{
    int lfd, cfd;
    int i, c;
    int num = 3;
    int id;
    char *port = "1234";
    peer_t *p;
    rad_t *rad;
    struct event_base *evb;

    while ((c = getopt(argc, argv, "l:n:v")) != -1) {
	switch(c) {
	case 'l':
	    port = optarg;
	    break;
	case 'n':
	    num = atoi(optarg);
	    break;
	case 'v':
	    debug++;
	    break;
	default: /* '?' */
	    fprintf(stderr, "Usage: %s [-l port] [-v] peer1 peer2 ...\n",
		    progname);
	    exit(EXIT_FAILURE);
	}
    }
    
    lfd = tcp_listen(port);
    if (lfd == -1) {
	return EXIT_FAILURE;
    }

    evb = event_base_new();
    if (! evb) {
        fprintf(stderr, "%s: creating event base failed\n", progname);
	return EXIT_FAILURE;
    }

    srand(time(NULL));
    id = (getpid() << 16) + (((rand() >> 8) & 0xffff));
    rad = rad_new(evb, id, lfd, num);

    for (i = optind; i < argc; i++) {
	char *s = strchr(argv[i], ':');
	cfd = -1;
	if (s) {
	    *s = '\0';
	    cfd = tcp_connect(argv[i], s+1);
	} else {
	    cfd = tcp_connect(argv[i], port);
	}
	if (cfd == -1) {
	    return EXIT_FAILURE;
	}
	p = peer_new(rad, cfd);
	rad_add_peer(rad, p);
    }

    if (event_base_loop(evb, 0) == -1) {
        fprintf(stderr, "%s: event loop failed\n", progname);
        event_base_free(evb);
	return EXIT_FAILURE;
    }

    event_base_free(evb);

    return EXIT_SUCCESS;
}
