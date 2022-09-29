/*
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * env.c
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/* environ is defined as a global variable
in the Glibc source file posix/environ.c*/
extern char **environ;

int main(int argc, char *argv[])
{
    int opt;
    argv[0] += 2; // removes "./" from "./env"

    // printf("\n\n%s\n", argv[0]); // ./env
    // return 0;

    // we need to parse the string into n commands provided
    // dynamically allocate string arrays for commands and strings
    // [command1, arg1, arg2 ..argn]
    // [command2, arg1, arg2 ..argn]

    while ((opt = getopt(argc, argv, "-:i0u:v")) != -1)
    {
        switch (opt)
        {
        case '?':
        {
            printf("Unknown Command!\n");
            _exit(0);
            break;
        }
        case ':':
        {
            printf("Missing argument!\n");
            _exit(0);
            break;
        }
        case 'i': // new env
        {
            execvp(argv[0], argv);
            break;
        }

        case 'u': //-u name, the program removes the variable name from the environment
        {
            execvp(argv[0], argv);
            break;
        }

        case 'v': // writes a trace of what it is doing to the standard error
        {
            execvp(argv[0], argv);
            break;
        }

        case 1:
        {
            execvp(argv[0], argv);
            break;
        }
        }
    }
    execvp(argv[0], argv); // print env
    return 0;
}
