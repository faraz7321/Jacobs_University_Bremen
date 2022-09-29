/*
 * echo/echo-pthread-sem.c --
 *
 *      A simple program to start and join threads. This version uses
 *      POSIX mutexes to make sure the threads print their arguments
 *      in the right order. Mutex error handling code has been left
 *      out in order to keep the code short.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct arg {
    char *msg;
    pthread_mutex_t gate;
    struct arg *next;
} arg_t;

static void* work(void *data)
{
    arg_t *arg = (arg_t *) data;

    (void) pthread_mutex_lock(&arg->gate);
    (void) printf("%s ", arg->msg);
    if (arg->next) {
        (void) pthread_mutex_unlock(&arg->next->gate);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int rc, status = EXIT_SUCCESS;
    pthread_t tids[argc];
    arg_t args[argc];

    memset(args, 0, sizeof(args));

    for (int i = 1; i < argc; i++) {
        arg_t *arg = &args[i];
        arg->msg = argv[i];
        (void) pthread_mutex_init(&arg->gate, NULL);
        (void) pthread_mutex_lock(&arg->gate);
        if (i < argc-1) {
            arg->next = &args[i+1];
        }
        rc = pthread_create(&tids[i], NULL, work, arg);
        if (rc) {
            fprintf(stderr, "pthread_create() failed: %s\n", strerror(rc));
            status = EXIT_FAILURE;
        }
    }
    if (argc > 1) {
        (void) pthread_mutex_unlock(&args[1].gate);
    }

    for (int i = 1; i < argc; i++) {
        if (tids[i]) {
            rc = pthread_join(tids[i], NULL);
            if (rc) {
                fprintf(stderr, "pthread_join() failed: %s\n", strerror(rc));
                status = EXIT_FAILURE;
            }
        }
        if (args[i].msg) {
            (void) pthread_mutex_destroy(&args[i].gate);
        }
    }

    (void) printf("\n");
    if (fflush(stdout) || ferror(stdout)) {
        perror("write failed");
        status = EXIT_FAILURE;
    }
    
    return status;
}
