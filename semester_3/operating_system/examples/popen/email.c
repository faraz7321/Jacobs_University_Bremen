/*
 * email.c --
 *
 *      Send an email by using the popen() / pclose() C library
 *      functions.
 */

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int
email(const char *to, const char *subject, const char *msg)
{
    FILE *f;
    char cmd[1024];

    snprintf(cmd, sizeof(cmd), "mail -s \"%s\" \"%s\"", subject, to);

    f = popen(cmd, "w");
    if (! f) {
        return 1;
    }
    fprintf(f, "%s\n", msg);
    fflush(f);
    if (ferror(f)) {
        pclose(f);
        return 2;
    }
    if (pclose(f)) {
        return 3;
    }
    return 0;
}

int
main(void)
{
    int s;

    s = email("j.schoenwaelder@jacobs-university.de",
	      "email test", "Hello World!");
    if (s) {
        fprintf(stderr, "email deliver failed - status code %d\n", s);
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
