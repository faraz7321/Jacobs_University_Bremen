/*
 * pee/pee.c --
 *
 *	This program demonstrates the usage of pipes by implementing
 *      a piped version of tee (hence the name pee).
 */

#define _POSIX_C_SOURCE 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

static const char *progname = "pee";

typedef struct {
    pid_t pid;
    int pipe[2];
} proc_t;

static int
cat(proc_t *child, int n)
{
    int i;
    char buffer[4096];
    ssize_t len;

    while ((len = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
	for (i = 0; i < n; i++) {
	    if (child[i].pid != -1) {
		if (write(child[i].pipe[1], buffer, len) != len) {
		    fprintf(stderr, "%s: writing to child %d (pid %d): %s\n",
			    progname, i+1, child[i].pid, strerror(errno));
		}
	    }
	}
    }

    if (len == 0) {
	for (i = 0; i < n; i++) {
	    if (child[i].pid != -1) {
		(void) close(child[i].pipe[1]);
	    }
	}
    }

    if (len < 0) {
	fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	return -1;
    }

    return 0;
}

static int
add(proc_t *child, const char *command)
{
    if (-1 == pipe(child->pipe)) {
	fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	return -1;
    }

    child->pid = fork();
    if (-1 == child->pid) {
	(void) close(child->pipe[0]);
	(void) close(child->pipe[1]);
	fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	return -1;
    }

    if (child->pid) {			/* parent */
	(void) close(child->pipe[0]);
    } else {				/* child */
	if (-1 == dup2(child->pipe[0], STDIN_FILENO)) {
	    fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	    _exit(EXIT_FAILURE);
	}
	(void) close(child->pipe[1]);
	execl("/bin/sh", "sh", "-c", command, (char *) NULL);
	_exit(EXIT_FAILURE);
    }

    return 0;
}

int
main(int argc, char *argv[])
{
    const char *usage = "Usage: %s command ...\n";
    int c, i;
    proc_t childs[argc];

    while ((c = getopt(argc, argv, "h")) >= 0) {
	switch (c) {
	case 'h':
	    printf(usage, progname);
	    exit(EXIT_SUCCESS);
	case ':':
	case '?':
	    exit(EXIT_FAILURE);
	}
    }
    argc -= optind;
    argv += optind;

    for (i = 0; i < argc; i++) {
	add(&childs[i], argv[i]);
    }

    cat(childs, argc);
    
    for (i = 0; i < argc; i++) {
	(void) waitpid(childs[i].pid, NULL, 0);
    }
    
    return EXIT_SUCCESS;
}
