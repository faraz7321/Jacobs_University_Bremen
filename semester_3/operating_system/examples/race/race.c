/*
 * race/race.c --
 *
 *      A simple program demonstrating race conditions. Note that it
 *      is system specific how frequently race conditions occur.  Run
 *      this program using
 *
 *          watch -n 0.5 -d "./race | sort -n | xargs -n 20"
 *
 *      and lean back and you may see numbers suddenly changing.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

static unsigned int c = 0;              /* shared variable */
static const struct timespec ts = { .tv_sec = 0, .tv_nsec = 123456 };

static void* count(void *ignored)
{
    (void) ignored;

    for (int i = 0; i < 10; i++) {
        nanosleep(&ts, NULL);
        printf("%d\n", ++c);
    }
    return NULL;
}

int main(void)
{
    const unsigned int num = 8;
    unsigned int i;
    int rc, status = EXIT_SUCCESS;
    pthread_t tids[num];

    for (i = 0; i < num; i++) {
        rc = pthread_create(&tids[i], NULL, count, NULL);
        if (rc) {
            fprintf(stderr, "pthread_create() failed: %s\n", strerror(rc));
            status = EXIT_FAILURE;
        }
    }

    for (i = 0; i < num; i++) {
        rc = pthread_join(tids[i], NULL);
        if (rc) {
            fprintf(stderr, "pthread_join() failed: %s\n", strerror(rc));
            status = EXIT_FAILURE;
        }
    }
    return status;
}
