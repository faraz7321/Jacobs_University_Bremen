/*
 * ls/main.c --
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

int
main(int argc, char *argv[])
{
    int c;
    int flags = 0;

    while ((c = getopt(argc, argv, "aln")) >= 0) {
        switch (c) {
        case 'a':
            flags |= LS_FLAG_ALL;
            break;
        case 'l':
            flags |= LS_FLAG_LONG;
            break;
        case 'n':
            flags |= LS_FLAG_NUMERIC;
            break;
        case ':':
        case '?':
            exit(EXIT_FAILURE);
        }
    }
    
    if (argc == optind) {
        ls(".", flags);
    } else {
        for (int i = optind; i < argc; i++) {
            ls(argv[i], flags);
        }
    }

    return EXIT_SUCCESS;
}
