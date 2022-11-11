/*
 * msh/util.c --
 *
 * Implementation of utility functions for the msh.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "msh.h"

void*
msh_malloc(size_t size)
{
    void *p;

    p = malloc(size);
    if (! p) {
	fprintf(stderr, "%s: out of memory\n", progname);
	exit(EXIT_FAILURE);
    }
    return p;
}

void *
msh_realloc(void *ptr, size_t size)
{
    void *p;

    p = realloc(ptr, size);
    if (! p) {
	fprintf(stderr, "%s: out of memory\n", progname);
	exit(EXIT_FAILURE);
    }
    return p;
}

char*
msh_strdup(const char *s)
{
    char *p;

    assert(s);
    
    p = msh_malloc(strlen(s)+1);
    strcpy(p, s);
    return p;
}

const char*
msh_home()
{
    const char *home = getenv("HOME");
    return home;
}
