/*
 * pthread/pthread-mutex.c --
 *
 *      A simple demonstration of pthread mutexes. This example
 *      lacks error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>

static unsigned int count = 0;          /* shared variable */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void* work(void *ignored)
{
    (void) ignored;
    
    (void) pthread_mutex_lock(&mutex);
    count++;
    (void) pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[argc];

    (void) argv;

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[i], NULL, work, NULL);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[i], NULL);
    }
    return 0;
}
