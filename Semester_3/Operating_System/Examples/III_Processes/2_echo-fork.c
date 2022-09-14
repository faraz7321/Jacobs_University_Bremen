/*
 * echo/echo-fork.c --
 *
 * A simple program to fork processes and to wait for them.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void work(const char *msg)
{
    (void)printf("%s ", msg);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    int stat, status = EXIT_SUCCESS;
    pid_t pids[argc];

    for (int i = 1; i < argc; i++)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork() failed");
            status = EXIT_FAILURE;
            continue;
        }
        if (pids[i] == 0)
        {
            work(argv[i]);
        }
    }

    for (int i = 1; i < argc; i++)
    {
        if (pids[i] > 0)
        {
            if (waitpid(pids[i], &stat, 0) == -1)
            {
                perror("waitpid() failed");
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