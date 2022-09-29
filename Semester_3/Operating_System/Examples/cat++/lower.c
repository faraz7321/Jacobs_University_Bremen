/*
 * cat++/lower.c
 *
 *	Implementation of a lowercase transformation.
 */

#include <ctype.h>

char *
transform(char *line)
{
    int i;

    for (i = 0; line[i]; i++) {
	line[i] = tolower(line[i]);
    }

    return line;
}
