/*
 * pthread/pthread-barrier.c --
 *
 *      A simple demonstration of pthread barriers. This example lacks
 *      error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdio.h>

typedef struct {
    pthread_barrier_t enter;            /* gate to enter work */
    pthread_barrier_t leave;            /* gate to leave work */
} gates_t;

typedef struct {
    char *name;                         /* name of the worker */
    gates_t *gates;                     /* gates to use */
} worker_t;

static void* work(void *arg)
{
    worker_t *me = (worker_t *) arg;

    printf("%s arriving\n", me->name);
    (void) pthread_barrier_wait(&me->gates->enter);
    printf("%s working\n", me->name);
    (void) pthread_barrier_wait(&me->gates->leave);
    printf("%s leaving\n", me->name);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[argc];
    gates_t gates;
    worker_t worker[argc];

    (void) pthread_barrier_init(&gates.enter, NULL, argc-1);
    (void) pthread_barrier_init(&gates.leave, NULL, argc-1);

    for (int i = 1; i < argc; i++) {
        worker[i].name = argv[i];
        worker[i].gates = &gates;
        (void) pthread_create(&tids[i], NULL, work, &worker[i]);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[i], NULL);
    }
    return 0;
}
