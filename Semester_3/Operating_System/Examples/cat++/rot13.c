/*
 * cat++/rot13.c
 *
 *	Implementation of the classic rot13 text transformation to
 *	be loaded as a dynamic library at runtime.
 */

#define ROT 13

char *
transform(char *line)
{
    int i;

    for (i = 0; line[i]; i++) {
	if (line[i] >='A' && line[i] <='Z') {
	    if ((line[i] + ROT) <= 'Z') {
		line[i] += ROT;
	    } else {
		line[i] -= ROT;
	    } 
	} else if (line[i] >='a' && line[i] <='z') {
	    if ((line[i] + ROT) <= 'z') {
		line[i] += ROT;
	    } else {
		line[i] -= ROT;
	    }
	}
    }

    return line;
}
