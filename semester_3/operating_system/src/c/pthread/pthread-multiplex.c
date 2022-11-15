/*
 * pthread/pthread-multiplex.c --
 *
 *      An implementation of the multiplex pattern using pthread
 *      mutexes and condition variables. This example lacks error
 *      handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <time.h>
#include <pthread.h>
#include <assert.h>

typedef struct {
    unsigned int counter;       /* shared counter */
    unsigned int max;           /* max number of threads */
    pthread_mutex_t mutex;      /* mutex protecting the counter */
    pthread_cond_t cond;        /* condition variable */
} counter_t;

static void* work(void *arg)
{
    counter_t *c = (counter_t *) arg;
    struct timespec duration = { .tv_sec = 0, .tv_nsec = 123456 };
    
    (void) pthread_mutex_lock(&c->mutex);
    while (c->counter >= c->max) {
          (void) pthread_cond_wait(&c->cond, &c->mutex);
    }
    c->counter++;
    assert(c->counter <= c->max);
    (void) pthread_mutex_unlock(&c->mutex);

    (void) nanosleep(&duration, NULL);          /* simulate some work */
    
    (void) pthread_mutex_lock(&c->mutex);
    c->counter--;
    (void) pthread_cond_signal(&c->cond);
    (void) pthread_mutex_unlock(&c->mutex);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[argc];
    counter_t cnter = { .counter = 0, .max = 3,
                        .mutex = PTHREAD_MUTEX_INITIALIZER,
                        .cond = PTHREAD_COND_INITIALIZER };
    (void) argv;

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[i], NULL, work, &cnter);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[i], NULL);
    }
    return 0;
}
