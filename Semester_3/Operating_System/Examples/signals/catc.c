/*
 * signals/catc.c --
 *
 *	This program demonstrates the C library functions for handling
 *	signals. Note that signal handlers need to be reinstalled and
 *	that signals can interrupt I/O system calls. As a consequence,
 *	the main loop needs to handle I/O failures caused by signals.
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static void sig_handler(int);

static void sig_install(void)
{
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
	perror("signal");
	exit(EXIT_FAILURE);
    }
}

static void sig_handler(int signum)
{
    if (signum == SIGINT) {
        fprintf(stderr, "catc: sig_handler: Interrupt\n");
        sig_install();
    } else {
        fprintf(stderr, "catc: sig_handler: %d\n", signum);
    }
}

int main(void)
{
    char c;

    sig_install();
    while (! feof(stdin)) {
        while ((c = getc(stdin)) != EOF) {
            (void) putc(c, stdout);
        }
        if (ferror(stdin)) {
            if (errno == EINTR) {
                clearerr(stdin);
                continue;
            }
            break;
        }
    }
    if (ferror(stdin) || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
