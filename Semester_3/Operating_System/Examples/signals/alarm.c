/*
 * signals/alarm.c --
 *
 *	Demonstration of interval timers and how to ignore signals
 *	coming from terminating child processes. What happens if the
 *	program does not request to ignore terminating child signals?
 *	What happens if the program requests to handle terminating
 *	child signals?
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

static void
handler(int signum)
{
#ifdef __APPLE__
    if (signum == SIGINT) {
        fprintf(stderr, "catp: handler: %s\n", strsignal(signum));
    }
#else
    psignal(signum, "catp: handler");
#endif
}

int
main(void)
{
    struct sigaction sa;
    pid_t pid;
    struct timespec delay = { .tv_sec = 0, .tv_nsec = 500000000 }, rem;
    struct itimerval itv = {
        { .tv_sec = 1, .tv_usec = 0 },  /* periodic interval */
        { .tv_sec = 2, .tv_usec = 0 }   /* time until next signal */
    };

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGALRM, &sa, NULL);      /* install SIGALRM handler */
    sigaction(SIGVTALRM, &sa, NULL);    /* install SIGVTALRM handler */

    sa.sa_handler = SIG_IGN;
    sigaction(SIGCHLD, &sa, NULL);      /* ignore SIGCHLD signals */

    if (setitimer(ITIMER_REAL, &itv, NULL) == -1) {
	perror("setitimer");
	return EXIT_FAILURE;
    }
    if (setitimer(ITIMER_VIRTUAL, &itv, NULL) == -1) {
	perror("setitimer");
	return EXIT_FAILURE;
    }

    while (1) {
	int n = 0, r = rand() & 0xffffff; /* generally not a smart idea */
	for (int i = 0; i < r; i++) {
	    n = (n-1) * (n-1);
	}
        for (rem = delay; nanosleep(&rem, &rem) == EINTR; ) ;
	if ((pid = fork()) == -1) {
	    perror("fork");
            exit(EXIT_FAILURE);
	}
        if (pid == 0) {
	    putchar('.');
	    exit(EXIT_SUCCESS);
	}
    }
    
    return EXIT_SUCCESS;
}
