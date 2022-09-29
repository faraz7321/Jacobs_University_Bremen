/*
 * pthread/pthread-rwlock.c --
 *
 *      A simple demonstration of pthread rwlocks. This example lacks
 *      error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>

static unsigned int count = 0;          /* shared variable */
static pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

static void* reader(void *ignored)
{
    (void) ignored;
    
    (void) pthread_rwlock_rdlock(&rwlock);
    int x = count + count;
    (void) x;
    (void) pthread_rwlock_unlock(&rwlock);
    return NULL;
}

static void* writer(void *ignored)
{
    (void) ignored;

    (void) pthread_rwlock_wrlock(&rwlock);
    count++;
    (void) pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[2*argc];
    (void) argv;

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[2*i], NULL, reader, NULL);
        (void) pthread_create(&tids[2*i+1], NULL, writer, NULL);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[2*i], NULL);
        (void) pthread_join(tids[2*i+1], NULL);
    }
    return 0;
}
