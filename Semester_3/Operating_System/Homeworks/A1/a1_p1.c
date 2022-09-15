/*
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * a1_p1.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char *strdup(const char *s)
{
    size_t len = strlen(s);

    // char d[len + 1]; // value of len needs to be constant.
    // need to be dynamically allocated
    char *d = malloc(len + 1);
    return strncpy(d, s, len + 1);
}

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++)
    {
        (void)puts(strdup(argv[i]));
    }

    return EXIT_SUCCESS;
}