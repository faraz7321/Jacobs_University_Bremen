/*
 * memmap/memmap.c --
 *
 *      This program demonstrates how to allocate memory using
 *      anonymous memory mappings. It also shows how information
 *      about memory mappings can be found on Linux systems.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memmap.h"

static const char *progname = "memmap";

int main(int argc, char *argv[])
{
    int c;
    int flags = 0;

    while ((c = getopt(argc, argv, "lvh")) >= 0) {
        switch (c) {
        case 'l':
            flags |= MEMMAP_L_FLAG;
            break;
        case 'v':
	    flags |= MEMMAP_V_FLAG;
            break;
        case 'h':
            printf("Usage: %s [-l] [-v]\n", progname);
            return EXIT_SUCCESS;
        }
    }

    mapit(flags);
    return EXIT_SUCCESS;
}
