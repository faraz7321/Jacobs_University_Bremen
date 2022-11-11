/*
 * signals/catp.c --
 *
 *	This program demonstrates the POSIX library functions for
 *	handling signals. The POSIX API allows programs much more
 *	control over the behaviour of signals and signal handlers. We
 *	request that system calls are restarted, which simplifies the
 *	main loop since we do not have to deal I/O call interrupts.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

static void sig_action(int signum, siginfo_t *siginfo, void *unused);

static void sig_install(void)
{
    struct sigaction sa;

    sa.sa_sigaction = sig_action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

static void sig_action(int signum, siginfo_t *siginfo, void *unused)
{
    (void) unused;
    if (siginfo && siginfo->si_code <= 0) {
        fprintf(stderr, "catp: sig_action: %s (from pid %d, uid %d)\n",
                strsignal(signum), siginfo->si_pid, siginfo->si_uid);
    } else {
        fprintf(stderr, "catp: sig_action: %s\n", strsignal(signum));
    }
}

int main(void)
{
    char c;

    sig_install();
    while ((c = getc(stdin)) != EOF) {
        (void) putc(c, stdout);
    }
    if (ferror(stdin) || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
