/*
 * ls/ls.c --
 *
 *	A very basic implementation of 'ls' demonstrating how to read
 *	directories and obtain status information about files using
 *	POSIX interfaces.
 */

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "ls.h"

void
ls(const char *path, int flags)
{
    DIR *d;
    struct dirent *e;
    
    d = opendir(path);
    if (! d) {
        perror("opendir");
        return;
    }

    if (chdir(path) == -1) {
        perror("chdir");
        return;
    }
    
    while (1) {
        e = readdir(d);
        if (! e) {
            break;
        }
        if ((flags & LS_FLAG_ALL) || e->d_name[0] != '.') {
            if (flags & LS_FLAG_LONG) {
		show(e, flags);
            } else {
                puts(e->d_name);
            }
        }
    }

    (void) closedir(d);
}
