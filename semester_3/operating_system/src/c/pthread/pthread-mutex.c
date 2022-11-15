/*
 * pthread/pthread-mutex.c --
 *
 *      A simple demonstration of pthread mutexes. This example
 *      lacks error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>

typedef struct {
    unsigned int counter;       /* shared counter */
    pthread_mutex_t mutex;      /* mutex protecting the counter */
} counter_t;

static void* work(void *arg)
{
    counter_t *c = (counter_t *) arg;
    
    (void) pthread_mutex_lock(&c->mutex);
    c->counter++;
    (void) pthread_mutex_unlock(&c->mutex);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[argc];
    counter_t cnter = { .counter = 0, .mutex = PTHREAD_MUTEX_INITIALIZER };

    (void) argv;

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[i], NULL, work, &cnter);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[i], NULL);
    }
    return 0;
}
