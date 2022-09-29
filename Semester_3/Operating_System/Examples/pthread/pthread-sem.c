/*
 * pthread/pthread-sem.c --
 *
 *      A simple demonstration of pthread semaphores. This example
 *      lacks error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <semaphore.h>

static unsigned int count = 0;          /* shared variable */
static sem_t sem;

static void* work(void *ignored)
{
    (void) ignored;

    (void) sem_wait(&sem);
    count++;
    (void) sem_post(&sem);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[argc];
    (void) argv;
    
    (void) sem_init(&sem, 0, 1);

    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[i], NULL, work, NULL);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[i], NULL);
    }
    return 0;
}
