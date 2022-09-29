/*
 * echo/echo.c --
 *
 *      A simple program to echo command line arguments.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
	(void) printf("%s ", argv[i]);
    }

    (void) printf("\n");
    if (fflush(stdout) || ferror(stdout)) {
        perror("write failed");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
