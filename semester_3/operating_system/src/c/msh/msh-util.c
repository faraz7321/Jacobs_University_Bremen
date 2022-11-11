/*
 * msh/msh-util.c --
 *
 *      This file contains utility functions for msh.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

const char *progname = "msh";

void
msh_show_prompt(void)
{
    printf("%s > ", progname);
    fflush(stdout);
}

static char*
next_token(char **s)
{
    char *token, *p;

    assert(s && *s);
    
    for (p = *s; *p && isspace(*p); p++) {
        *p = '\0';
    }
    token = p;
    for (; *p && !isspace(*p); p++) ;
    for (; *p && isspace(*p); p++) {
        *p = '\0';
    }
    *s = p;
    return token;
}

void
msh_read_command(FILE *stream, int *argc, char ***args)
{
#ifndef BUFLEN
#define BUFLEN 512
#endif
    static char line[BUFLEN];
    static char* argv[BUFLEN];
    char *p;

    assert(argc && args);

    memset((char *) argv, 0, sizeof(argv));
    p = fgets(line, sizeof(line), stream);
    for (*argc = 0; p && *p; (*argc)++) {
        argv[*argc] = next_token(&p);
    }
    *args = argv;
}
