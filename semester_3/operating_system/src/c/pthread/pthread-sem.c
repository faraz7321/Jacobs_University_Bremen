/*
 * pthread/pthread-sem.c --
 *
 *      A simple demonstration of pthread semaphores. This example
 *      lacks error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <semaphore.h>

typedef struct {
    unsigned int counter;       /* shared counter */
    sem_t semaphore;            /* mutex semaphore protecting the counter */
} counter_t;

static void* work(void *arg)
{
    counter_t *c = (counter_t *) arg;

    (void) sem_wait(&c->semaphore);
    c->counter++;
    (void) sem_post(&c->semaphore);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[argc];
    counter_t cnter = { .counter = 0  };
    (void) argv;
    
    (void) sem_init(&cnter.semaphore, 0, 1);

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[i], NULL, work, &cnter);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[i], NULL);
    }
    return 0;
}
