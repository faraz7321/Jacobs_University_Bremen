/*
 * memmap/pmap.c
 *
 *	Print the memory map of the running process as this allows us
 *	to see how the program changes the memory mappings. This only
 *	works on Linux since we need the pmap command.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memmap.h"

void
pmap(const char *msg, int flags)
{
    char cmd[1234];

    if (flags & MEMMAP_V_FLAG) {
	if (msg) {
	    printf("\n===> %s:\n", msg);
	    fflush(stdout);
	}
	snprintf(cmd, sizeof(cmd), "pmap -x %d",  getpid());
	system(cmd);
    }
}
