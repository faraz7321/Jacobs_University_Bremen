/*
 * parallel/parallel-simple.c --
 *
 *	A very stripped down version of GNU's parallel. See the
 *      first homework assignment, Operating Systems Spring 2015.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

static const char marker[] = ":::";

int main(int argc, char **argv)
{
    int m, j, status, code;
    pid_t pid;

    /*
     * Locate the marker in the command line arguments.
     */

    for (m = 0; m < argc; m++) {
	if (strcmp(argv[m], marker) == 0) {
	    break;
	}
    }

    if (m == argc) {
	fprintf(stderr, "parallel: no marker '%s' on the command line\n",
		marker);
	return EXIT_FAILURE;
    }

    /*
     * Fork child processes to do the work by placing each argument at
     * the marker position we have found. Since we are lazy, we simply
     * modify argv so that we do not need to allocate any memory.
     */

    for (j = m + 1; j < argc; j++) {
	argv[m] = argv[j];
	argv[m+1] = NULL;
	
	pid = fork();
	if (pid == -1) {
	    perror("parallel: fork");
	    continue;
	}
	if (pid == 0) {
	    execvp(argv[1], &(argv[1]));
	    perror("parallel: exec");
	    _exit(EXIT_FAILURE);
	}
    }

    /*
     * Wait for child processes to finish by waiting for any child to
     * die (waitpid() will return -1 and set errno = ECHILD if there
     * are no more child processes).
     */

    status = EXIT_SUCCESS;
    while (1) {
	if (waitpid(-1, &code, 0) == -1) {
	    if (errno != ECHILD) {
		perror("parallel: waitpid");
	    }
	    break;
	}
	if (WIFEXITED(code) && WEXITSTATUS(code)) {
	    status = EXIT_FAILURE;
	}
    }

    return status;
}
