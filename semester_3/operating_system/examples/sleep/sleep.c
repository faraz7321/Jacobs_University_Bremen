/*
 * sleep/sleep.c --
 *
 *	Implementation of sleep() using POSIX signal functions.
 */

#define _POSIX_C_SOURCE 2

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t wake_up = 0;

static void catch_alarm(int signum)
{
    (void) signum;              /* unused signum parameter */
    wake_up = 1;
}

unsigned int sleep(unsigned int seconds)
{
    struct sigaction sa, old_sa;
    sigset_t mask, old_mask;

    sa.sa_handler = catch_alarm;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    /* Be nice and save the original signal handler so that it can be
     * restored when we are done. */
    sigaction(SIGALRM, &sa, &old_sa);

    /* After resetting wake_up, ask the system to send us a SIGALRM at
     * an appropriate time. */
    wake_up = 0;
    alarm(seconds);

    /* First block the signal SIGALRM. After safely checking wake_up,
     * suspend until a signal arrives. Note that sigsuspend may return
     * on other signals (according to the old mask). If wake_up is
     * finally true, cleanup by unblocking the blocked signals. */
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_BLOCK, &mask, &old_mask);

    /* No SIGALRM will be delievered here since this signal is blocked.
     * This means we have a safe region here until we suspend below... */
    while (! wake_up) {
        sigsuspend(&old_mask);
    }

    /* Cleanup by restoring the original state. */
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sigaction(SIGALRM, &old_sa, NULL);
    return 0;
}
