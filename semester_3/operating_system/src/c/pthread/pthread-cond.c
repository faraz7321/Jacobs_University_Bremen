/*
 * pthread/pthread-cond.c --
 *
 *      A simple demonstration of pthread condition variables. This
 *      example lacks error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>

typedef struct {
    unsigned int counter;       /* shared counter */
    pthread_mutex_t mutex;      /* mutex protecting the counter */
    pthread_cond_t cond;        /* condition variable */
} counter_t;

static void* even(void *arg)
{
    counter_t *c = (counter_t *) arg;
    (void) pthread_mutex_lock(&c->mutex);
    while (c->counter % 2 != 0) {
        (void) pthread_cond_wait(&c->cond, &c->mutex);
    }
    c->counter++;
    (void) pthread_mutex_unlock(&c->mutex);
    (void) pthread_cond_signal(&c->cond);
    return NULL;
}

static void* odd(void *arg)
{
    counter_t *c = (counter_t *) arg;
    (void) pthread_mutex_lock(&c->mutex);
    while (c->counter % 2 == 0) {
        (void) pthread_cond_wait(&c->cond, &c->mutex);
    }
    c->counter++;
    (void) pthread_mutex_unlock(&c->mutex);
    (void) pthread_cond_signal(&c->cond);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[2*argc];
    counter_t cnter = { .counter = 0, .mutex = PTHREAD_MUTEX_INITIALIZER,
                        .cond = PTHREAD_COND_INITIALIZER };
    (void) argv;
    
    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[2*i], NULL, even, &cnter);
        (void) pthread_create(&tids[2*i+1], NULL, odd, &cnter);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[2*i], NULL);
        (void) pthread_join(tids[2*i+1], NULL);
    }
    return 0;
}
