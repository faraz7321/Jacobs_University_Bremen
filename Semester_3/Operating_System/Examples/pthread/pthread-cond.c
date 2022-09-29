/*
 * pthread/pthread-cond.c --
 *
 *      A simple demonstration of pthread condition variables. This
 *      example lacks error handling code to keep it short.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>

static unsigned int count = 0;          /* shared variable */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void* even(void *ignored)
{
    (void) ignored;
    
    (void) pthread_mutex_lock(&mutex);
    while (count % 2 != 0) {
        (void) pthread_cond_wait(&cond, &mutex);
    }
    count++;
    (void) pthread_mutex_unlock(&mutex);
    (void) pthread_cond_signal(&cond);
    return NULL;
}

static void* odd(void *ignored)
{
    (void) ignored;

    (void) pthread_mutex_lock(&mutex);
    while (count % 2 == 0) {
        (void) pthread_cond_wait(&cond, &mutex);
    }
    count++;
    (void) pthread_mutex_unlock(&mutex);
    (void) pthread_cond_signal(&cond);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tids[2*argc];
    (void) argv;
    
    for (int i = 1; i < argc; i++) {
        (void) pthread_create(&tids[2*i], NULL, even, NULL);
        (void) pthread_create(&tids[2*i+1], NULL, odd, NULL);
    }
    for (int i = 1; i < argc; i++) {
        (void) pthread_join(tids[2*i], NULL);
        (void) pthread_join(tids[2*i+1], NULL);
    }
    return 0;
}
