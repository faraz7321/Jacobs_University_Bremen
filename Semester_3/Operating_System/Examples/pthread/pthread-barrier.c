/*
 * pthread/pthread-barrier.c --
 *
 *      A simple demonstration of pthread barriers. This example lacks
 *      error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdio.h>

static pthread_barrier_t opening;
static pthread_barrier_t closing;

static void* work(void *arg)
{
    char *me = (char *) arg;

    printf("%s arriving\n", me);
    (void) pthread_barrier_wait(&opening);
    printf("%s working\n", me);
    (void) pthread_barrier_wait(&closing);
    printf("%s leaving\n", me);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[argc];

    (void) pthread_barrier_init(&opening, NULL, argc-1);
    (void) pthread_barrier_init(&closing, NULL, argc-1);

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[i], NULL, work, argv[i]);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[i], NULL);
    }
    return 0;
}
