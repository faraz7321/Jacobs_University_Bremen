/*
 * pipe/pipex.c --
 *
 *	This program sends data read from the standard input into a
 *	pipe connected to a child process. The child process copies
 *	data from the pipe to the standard output. This version simply
 *	uses the cat utility after duplicating the file descriptors.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Duplicate the source fd (sfd) to the destination fd (dfd), close
 * other fds referring to the pipe, and finally execute "cat".
 */

static void cat(int *pfd, int sfd, int dfd)
{
    if (dup2(sfd, dfd) == -1) {
	perror("dup2");
	exit(EXIT_FAILURE);
    }
    (void) close(pfd[0]);
    (void) close(pfd[1]);
    execlp("cat", "cat", NULL);
    perror("execl");
    exit(EXIT_FAILURE);
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
	cat(pfd, pfd[0], STDIN_FILENO);
    } else {
	cat(pfd, pfd[1], STDOUT_FILENO);
    }

    return EXIT_SUCCESS;
}
