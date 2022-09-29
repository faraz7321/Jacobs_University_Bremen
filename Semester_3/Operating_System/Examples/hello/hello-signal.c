/*
 * hello-signal.c --
 *
 *	This program which uses the stdio library to print a short
 *	message. The characters are printed whenever a SIGINT signal
 *	has been received and the process terminates via a SIGTERM
 *	signal when the entire message has been printed.
 *
 * Exercise:
 *
 * What happens if the mainloop implements a cat(1) loop? What is the
 * effect of the SA_RESTART flag?
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static const char *p = "Hello World\n";

static void
hello(int signo)
{
    (void) signo;

    (void) putc(*p, stdout);
    (void) fflush(stdout);
    p++;
    if (!p || !*p) {
        raise(SIGTERM);
    }
}

int
main(void)
{
    struct sigaction sa;
    sigset_t mask;
    
    sa.sa_handler = hello;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    sigemptyset(&mask);
    while (1) {
        sigsuspend(&mask);
    }

    return EXIT_SUCCESS;
}

