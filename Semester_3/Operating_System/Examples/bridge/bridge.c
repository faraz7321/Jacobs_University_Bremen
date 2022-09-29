/*
 * bridge/bridge.c --
 *
 *	An old bridge which crosses a river from east to west. Since
 *	it is a small bridge, cars can only go in one direction at a
 *	time and no more than 3 cars are allowed on the bridge.
 */

#define _REENTRANT
#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>

#define BRIDGE_DIRECTION_EAST 0x01
#define BRIDGE_DIRECTION_WEST 0x02

typedef struct bridge {
    int cars;
    int direction;
    pthread_mutex_t mutex;
    pthread_cond_t  empty;
} bridge_t;

static bridge_t shared_bridge = {
    .cars = 0,
    .direction = BRIDGE_DIRECTION_WEST,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .empty = PTHREAD_COND_INITIALIZER,
};

static const char *progname = "bridge";

static void
trace(char *event, bridge_t *bridge, int direction)
{
    fprintf(stderr, "car %s %s \t[bridge direction = %s, cars = %d] \n",
            event,
            direction == BRIDGE_DIRECTION_WEST ? "west" : "east",
            bridge->direction == BRIDGE_DIRECTION_WEST ? "west" : "east",
            bridge->cars);
}

/*
 * First wait until there are either no cars on the bridge or less
 * than two cars traveling into our direction. If there are no cars,
 * we can just define the new direction.
 */

static void
arrive(bridge_t *bridge, int direction)
{
    pthread_mutex_lock(&bridge->mutex);
    trace("arriving", bridge, direction);
    while (bridge->cars > 0 &&
           (bridge->cars > 2 || bridge->direction != direction)) {
        pthread_cond_wait(&bridge->empty, &bridge->mutex);
    }
    if (bridge->cars == 0) {
        bridge->direction = direction;
    }
    bridge->cars++;
    pthread_mutex_unlock(&bridge->mutex);
}

/*
 * Crossing the bridge is easy - just some delay. Note that without
 * calling sleep(), there is a good chance that threads will just run
 * until completion, which is kind of boring.
 */

static void
cross(bridge_t *bridge)
{
    trace("crossing", bridge, bridge->direction);
    sleep(1);
}

/*
 * Leave the bridge by waking up other cars who might be waiting
 * in front of the bridge.
 */

static void
leave(bridge_t *bridge)
{
    pthread_mutex_lock(&bridge->mutex);
    bridge->cars--;
    trace("leaving ", bridge, bridge->direction);
    pthread_cond_broadcast(&bridge->empty);
    pthread_mutex_unlock(&bridge->mutex);
}

/*
 * All cars implement the same behavior.
 */

static void
drive(bridge_t *bridge, int direction)
{
    sleep(1);
    arrive(bridge, direction);
    cross(bridge);
    leave(bridge);
}

/*
 * Entry point for threads going east.
 */

static void*
east(void *data)
{
    drive((bridge_t *) data, BRIDGE_DIRECTION_EAST);
    return NULL;
}

/*
 * Entry point for threads going west.
 */

static void*
west(void *data)
{
    drive((bridge_t *) data, BRIDGE_DIRECTION_WEST);
    return NULL;
}

/*
 * Run nw threads to go west and ne threads to go east. This function
 * could be smarter to introduce some random delays and to alternate
 * better between west-bound and east-bound cars.
 */

static int
run(int nw, int ne)
{
    int err, n = nw + ne;
    pthread_t thread[n];

    for (int i = 0; i < n; i++) {
	err = pthread_create(&thread[i], NULL,
			     i < nw ? east : west, &shared_bridge);
        if (err) {
	    fprintf(stderr, "%s: %s(): unable to create thread %d: %s\n",
		    progname, __func__, i, strerror(err));
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n; i++) {
        if (thread[i]) {
	    err = pthread_join(thread[i], NULL);
	    if (err) {
		fprintf(stderr, "%s: %s(): unable to join thread %d: %s\n",
			progname, __func__, i, strerror(err));
	    }
	}
    }

    return EXIT_SUCCESS;
}

int
main(int argc, char *argv[])
{
    int c, nw = 1, ne = 1;
    
    while ((c = getopt(argc, argv, "e:w:h")) >= 0) {
        switch (c) {
        case 'e':
            if ((ne = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of cars going east must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'w':
            if ((nw = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of cars going west must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            printf("Usage: %s [-e east] [-w west] [-h]\n", progname);
            exit(EXIT_SUCCESS);
        }
    }

    return run(nw, ne);
}
