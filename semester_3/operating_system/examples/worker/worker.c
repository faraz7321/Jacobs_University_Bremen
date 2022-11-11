/*
 * worker/worker.c --
 *
 *	A simple program demonstrating the "thread pool pattern". The
 *	dispatching thread reads numbers from stdin and places them
 *	into a queue processed by a fixed number of worker threads.
 *	Once the end of the input has been reached, the worker threads
 *	exit when the queue becomes empty. The queue is implemented
 *	using a fixed size bounded buffer.
 */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 128
#define BUFFER_CLOSED 0x01

typedef struct {
    unsigned int    count;
    long int        data[BUFFER_SIZE];
    int             in;
    int             out;
    int		    flags;
    pthread_mutex_t mutex;
    pthread_cond_t  empty;
    pthread_cond_t  full;
} buffer_t;

static buffer_t buffer = {
    .count = 0,
    .in    = 0,
    .out   = 0,
    .flags = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .empty = PTHREAD_COND_INITIALIZER,
    .full  = PTHREAD_COND_INITIALIZER
};

static const char *progname = "worker";

static long int
f(long int n)
{
    usleep(n * 100);
    return n > 100 ? n-10 : f(f(n+11));
}


static void *
worker(void *data)
{
    long int x = 0;
    buffer_t *queue = (buffer_t *) data;

    assert(queue);

    while (1) {
        pthread_mutex_lock(&queue->mutex);
        while (queue->count == 0) {
	    if (queue->flags & BUFFER_CLOSED) {
		pthread_mutex_unlock(&queue->mutex);
		return NULL;
	    }
            pthread_cond_wait(&queue->full, &queue->mutex);
        }
	
        x = queue->data[queue->out];
        queue->out = (queue->out + 1) % BUFFER_SIZE;
        queue->count--;
        pthread_cond_signal(&queue->empty);
        pthread_mutex_unlock(&queue->mutex);

	/* Note that stdio meanwhile is by default thread-safe. See
	   also flockfile(3) for more details how this works. */
	printf("f(%ld) = \t%ld\n", x, f(x));
    }

    return NULL;
}


static int
run(int n, buffer_t *queue)
{
    int err;
    long int x;
    pthread_t thread[n];
    char buffer[128], *end;

    assert(queue && n > 0);

    for (int i = 0; i < n; i++) {
	err = pthread_create(&thread[i], NULL, worker, queue);
	if (err) {
	    fprintf(stderr, "%s: %s: unable to create thread %d: %d\n",
		    progname, __func__, i, err);
	    return EXIT_FAILURE;
	}
    }

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
	if (strlen(buffer)) buffer[strlen(buffer)-1] = 0;
	x = strtol(buffer,  &end, 10);
	if (*end) continue;

	pthread_mutex_lock(&queue->mutex);
        while (queue->count == BUFFER_SIZE) {
            pthread_cond_wait(&queue->empty, &queue->mutex);
        }
        queue->data[queue->in] = x;
        queue->in = (queue->in + 1) % BUFFER_SIZE;
        queue->count++;
        pthread_cond_signal(&queue->full);
        pthread_mutex_unlock(&queue->mutex);
    }

    pthread_mutex_lock(&queue->mutex);
    queue->flags |= BUFFER_CLOSED;
    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_broadcast(&queue->full);

    for (int i = 0; i < n; i++) {
	if (thread[i]) (void) pthread_join(thread[i], NULL);
    }

    return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{
    int c;
    int nw = 3;
    
    while ((c = getopt(argc, argv, "w:h")) >= 0) {
	switch (c) {
	case 'w':
	    if ((nw = atoi(optarg)) <= 0) {
		fprintf(stderr, "number of worker threads must be > 0\n");
		exit(EXIT_FAILURE);
	    }
	    break;
	case 'h':
	    printf("Usage: %s [-w num-worker] [-h]\n", progname);
	    exit(EXIT_SUCCESS);
	}
    }

    return run(nw, &buffer);
}
