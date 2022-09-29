/*
 * bounded/bounded.c --
 *
 *      Bounded buffer (producer / consumer) problem solution with
 *      pthreads and condition variables.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>
#include <pthread.h>

#define BUFFER_SIZE 12

typedef struct buffer {
    unsigned int    count;
    unsigned int    data[BUFFER_SIZE];
    int             in;
    int             out;
    pthread_mutex_t mutex;
    pthread_cond_t  empty;
    pthread_cond_t  full;
} buffer_t;

static buffer_t shared_buffer = {
    .count = 0,
    .in    = 0,
    .out   = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .empty = PTHREAD_COND_INITIALIZER,
    .full  = PTHREAD_COND_INITIALIZER
};

static const char *progname = "bounded";

static unsigned int
next()
{
    static unsigned int cnt = 0;
    return ++cnt;
}

static void
check(unsigned int num)
{
    static unsigned int cnt = 0;
    assert(num == ++cnt);
}

static void*
producer(void *data)
{
    buffer_t *buffer = (buffer_t *) data;

    while (1) {
        (void) pthread_mutex_lock(&buffer->mutex);
        while (buffer->count == BUFFER_SIZE) {
            (void) pthread_cond_wait(&buffer->empty, &buffer->mutex);
        }
        buffer->data[buffer->in] = next();
        buffer->in = (buffer->in + 1) % BUFFER_SIZE;
        buffer->count++;
        (void) pthread_cond_signal(&buffer->full);
        (void) pthread_mutex_unlock(&buffer->mutex);
    }
    return NULL;
}

static void*
consumer(void *data)
{
    buffer_t *buffer = (buffer_t *) data;
        
    while (1) {
        (void) pthread_mutex_lock(&buffer->mutex);
        while (buffer->count == 0) {
            (void) pthread_cond_wait(&buffer->full, &buffer->mutex);
        }
        check(buffer->data[buffer->out]);
        buffer->out = (buffer->out + 1) % BUFFER_SIZE;
        buffer->count--;
        (void) pthread_cond_signal(&buffer->empty);
        (void) pthread_mutex_unlock(&buffer->mutex);
    }
    return NULL;
}

static int
run(int nc, int np)
{
    int err, n = nc + np;
    pthread_t thread[n];

    for (int i = 0; i < n; i++) {
        err = pthread_create(&thread[i], NULL,
                             i < nc ? consumer : producer, &shared_buffer);
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
    int c, nc = 1, np = 1;
    
    while ((c = getopt(argc, argv, "c:p:h")) >= 0) {
        switch (c) {
        case 'c':
            if ((nc = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of consumers must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'p':
            if ((np = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of producers must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            printf("Usage: %s [-c consumers] [-p producers] [-h]\n", progname);
            exit(EXIT_SUCCESS);
        }
    }

    return run(nc, np);
}
