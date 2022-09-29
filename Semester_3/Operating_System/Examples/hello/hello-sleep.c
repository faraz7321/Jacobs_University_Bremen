/*
 * hello-sleep.c --
 *
 *	This program which uses the stdio library to print a short
 *	message. Note that we check the return code of puts() and that
 *	we flush() the buffered output stream manually to check
 *	whether writing to stdout actually worked. This version does a
 *	nanosleep() after printing each character.
 *
 * Exercise:
 *
 * What happens if you do the flush() call after the end of the loop
 * instead of in the loop?
 */

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(void)
{
    const char msg[] = "Hello World\n";
    const char *p;
    struct timespec delay = { .tv_sec = 0, .tv_nsec = 100 * 1000 * 1000 };

    for (p = msg; *p; p++) {
        nanosleep(&delay, NULL);
        if (putc(*p, stdout) == EOF) {
	    return EXIT_FAILURE;
	}
        if (fflush(stdout) == EOF) {
	    return EXIT_FAILURE;
	}
    }
    
    return EXIT_SUCCESS;
}
