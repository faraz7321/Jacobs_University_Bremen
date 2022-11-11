/*
 * cat++/upper.c
 *
 *	Implementation of an uppercase transformation.
 */

#include <ctype.h>

char *
transform(char *line)
{
    int i;

    for (i = 0; line[i]; i++) {
	line[i] = toupper(line[i]);
    }

    return line;
}
