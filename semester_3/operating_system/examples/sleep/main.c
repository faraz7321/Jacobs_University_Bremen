/*
 * sleep/main.c --
 *
 *	This little example calls sleep().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++) {
	sleep(atoi(argv[i]));
    }
    
    return EXIT_SUCCESS;
}
