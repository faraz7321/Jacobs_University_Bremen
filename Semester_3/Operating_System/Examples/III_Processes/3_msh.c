/*
 * msh/msh.c --
 *
 * This file contains the simple and stupid shell (msh).
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

#include "msh.h"

int main()
{
    pid_t pid;
    int status;
    int argc;
    char **argv;

    while (1)
    {
        msh_show_prompt();
        msh_read_command(stdin, &argc, &argv);
        if (argv[0] == NULL || strcmp(argv[0], "exit") == 0)
        {
            break;
        }
        if (strlen(argv[0]) == 0)
        {
            continue;
        }
        pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "%s: fork: %s\n", progname, strerror(errno));
            continue;
        }
        if (pid == 0)
        { /* child */
            execvp(argv[0], argv);
            fprintf(stderr, "%s: execvp: %s\n", progname, strerror(errno));
            _exit(EXIT_FAILURE);
        }
        else
        { /* parent */
            if (waitpid(pid, &status, 0) == -1)
            {
                fprintf(stderr, "%s: waitpid: %s\n", progname, strerror(errno));
            }
        }
    }

    return EXIT_SUCCESS;
}
