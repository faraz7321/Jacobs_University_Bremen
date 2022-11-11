/*
 * pipe/pipe.c --
 *
 *	This program sends data read from the standard input into a
 *	pipe connected to a child process. The child process copies
 *	data from the pipe to the standard output.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void copy(int sfd, int dfd)
{
    char buf[128];
    size_t len;
    
    while ((len = read(sfd, buf, sizeof(buf))) > 0) {
        (void) write(dfd, buf, len);
    }
}

int main(void)
{
    int pfd[2];
    pid_t pid;

    if (pipe(pfd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (pid == 0) {
        (void) close(pfd[1]);
        copy(pfd[0], STDOUT_FILENO);
        (void) close(pfd[0]);
    } else {
        (void) close(pfd[0]);
        copy(STDIN_FILENO, pfd[1]);
        (void) close(pfd[1]);
    }

    return EXIT_SUCCESS;
}
