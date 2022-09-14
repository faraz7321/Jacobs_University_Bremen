/*
 * echo/echo-pthread.c --
 *
 * A simple program to start and join threads.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

static void *work(void *data)
{
    char *msg = (char *)data;
    (void)printf("%s ", msg);
    return NULL;
}

int main(int argc, char *argv[])
{
    int rc, status = EXIT_SUCCESS;
    pthread_t tids[argc];

    for (int i = 1; i < argc; i++)
    {
        rc = pthread_create(&tids[i], NULL, work, argv[i]);
        if (rc)
        {
            fprintf(stderr, "pthread_create() failed: %s\n", strerror(rc));
            status = EXIT_FAILURE;
        }
    }

    for (int i = 1; i < argc; i++)
    {
        if (tids[i])
        {
            rc = pthread_join(tids[i], NULL);
            if (rc)
            {
                fprintf(stderr, "pthread_join() failed: %s\n", strerror(rc));
                status = EXIT_FAILURE;
            }
        }
    }

    (void)printf("\n");
    if (fflush(stdout) || ferror(stdout))
    {
        perror("write failed");
        status = EXIT_FAILURE;
    }

    return status;
}