/*
 * pthread/pthread-rwlock.c --
 *
 *      A simple demonstration of pthread rwlocks. This example lacks
 *      error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>

typedef struct {
    unsigned int counter;       /* shared counter */
    pthread_rwlock_t rwlock;    /* read/write lock for the counter */
} counter_t;

static void* reader(void *arg)
{
    counter_t *c = (counter_t *) arg;
    
    (void) pthread_rwlock_rdlock(&c->rwlock);
    (void) (c->counter + c->counter);
    (void) pthread_rwlock_unlock(&c->rwlock);
    return NULL;
}

static void* writer(void *arg)
{
    counter_t *c = (counter_t *) arg;

    (void) pthread_rwlock_wrlock(&c->rwlock);
    c->counter++;
    (void) pthread_rwlock_unlock(&c->rwlock);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[2*argc];
    counter_t cnter = { .counter = 0, .rwlock = PTHREAD_RWLOCK_INITIALIZER };
    (void) argv;

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[2*i], NULL, reader, &cnter);
        (void) pthread_create(&tids[2*i+1], NULL, writer, &cnter);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[2*i], NULL);
        (void) pthread_join(tids[2*i+1], NULL);
    }
    return 0;
}
