/*
 * parallel/parallel.c --
 *
 *	A very stripped down version of GNU's parallel. See the
 *      first homework assignment, Operating Systems Spring 2015.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static const char marker[] = ":::";
static int verbose = 0;

/*
 * Find the first marker in the command line vector. Abort with an
 * error if the marker can't be found.
 */

static int
find_marker(int argc, char *argv[])
{
    int m;
    
    for (m = optind; m < argc; m++) {
	if (strcmp(argv[m], marker) == 0) {
	    break;
	}
    }

    if (m == argc) {
	fprintf(stderr, "parallel: no marker '%s' on the command line\n",
		marker);
	exit(EXIT_FAILURE);
    }

    return m;
}

/*
 * Wait for one child processes to finish by waiting for any child to
 * die (waitpid() will return -1 and set errno = ECHILD if there are
 * no more child processes). If the child did terminate with a
 * non-zero exit code, return EXIT_FAILURE in status. Note that
 * waitpid() may return for other reasons, so we need a loop here.
 */

static int
wait_for_one(int *status)
{
    int code;
    pid_t pid;

    do {
        pid = waitpid(-1, &code, 0);
	if (pid == -1) {
	    return -1;
	}
	if (WIFEXITED(code)) {
	    if (verbose) {
	        printf("parallel: [%d] exit: %d\n", pid, WEXITSTATUS(code));
	    }
	    if (WEXITSTATUS(code) && status) {
	        *status = EXIT_FAILURE;
	    }
	}
    } while (! WIFEXITED(code));
    return 0;
}

/*
 * Wait for all child processes to finish by repeatedly waiting for
 * another child to finish.
 */

static void
wait_for_all(int *status)
{
    while (wait_for_one(status) != -1) ;
}

/*
 * Fork child processes to do the work by placing each argument at the
 * marker position given by m. Since we are lazy, we simply modify
 * argv so that we do not need to allocate any memory.
 */

static void
run_commands(int argc, char *argv[], int m, int jobs, int *status)
{
    int j, cnt = 0;
    pid_t pid;
  
    for (j = m + 1; j < argc; j++) {
	argv[m] = argv[j];
	argv[m+1] = NULL;

	if (jobs > 0 && cnt == jobs) {
 	    (void) wait_for_one(status);
	    cnt--;
	}
	
	pid = fork();
	if (pid == -1) {
	    perror("parallel: fork");
	    continue;
	}
	if (pid == 0) {
	    execvp(argv[0], argv);
	    perror("parallel: exec");
	    _exit(EXIT_FAILURE);
	} else {
	    cnt++;
	    if (verbose) {
	        printf("parallel: [%d] exec: ", pid);
		for (int a = 0; argv[a]; a++) {
		    printf("%s ", argv[a]);
		}
		printf("\n");
	    }
	}
    }
}

int main(int argc, char *argv[])
{
    int c, m, jobs = 0, status = EXIT_SUCCESS;
    char *end;

    while ((c = getopt(argc, argv, "hj:v")) >= 0) {
        switch (c) {
	case 'j':
	    jobs = (int) strtol(optarg, &end, 10);
	    if (*end || jobs < 0) {
		fprintf(stderr, "parallel: number of jobs must be a non-negative decimal number\n");
		exit(EXIT_FAILURE);
	    }
	    break;
	case 'h':
	    printf("Usage: parallel [-h ] [-j jobs] [-v] cmd arg [...] ::: arg [...]\n");
	    exit(EXIT_SUCCESS);
	case 'v':
	    verbose = 1;
	    break;
	}
    }

    m = find_marker(argc, argv);
    run_commands(argc - optind, &argv[optind], m - optind, jobs, &status);
    wait_for_all(&status);

    return status;
}
