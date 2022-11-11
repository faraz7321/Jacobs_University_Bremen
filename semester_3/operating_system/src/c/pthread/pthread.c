/*
 * pthread/pthread.c --
 *
 *      A simple program to create and join threads.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <string.h>
#include <stdio.h>

static void* work(void *data)
{
    (void) data;
    return NULL;
}

int main(int argc, char *argv[])
{
    int rc;
    pthread_t tids[argc];

    (void) argv;
    
    for (int i = 1; i < argc; i++) {
        rc = pthread_create(&tids[i], NULL, work, NULL);
        if (rc) {
            fprintf(stderr, "pthread_create(): %s\n", strerror(rc));
        }
    }

    for (int i = 1; i < argc; i++) {
        if (tids[i]) {
            rc = pthread_join(tids[i], NULL);
            if (rc) {
                fprintf(stderr, "pthread_join(): %s\n", strerror(rc));
            }
        }
    }
    
    return 0;
}
