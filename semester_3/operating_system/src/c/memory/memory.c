/*
 * memory/memory.c --
 *
 *	A program demonstrating various memory related programming
 *	errors. Commands line arguments can be used to trigger a
 *	certain sequence of memory related programming errors.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SIZE 42

static char a[SIZE];
static char *b = "hello";

static void foo(char w, int n)
{
    char c[SIZE];
    char d[n];
    char *e;

    e = malloc(SIZE);
    if (! e) {
	perror("malloc");
	exit(EXIT_FAILURE);
    }
    memset(e, 0, SIZE);

    switch (w) {
    case 'a':		/* access of an already free'd region */
	free(e);
	assert(*e == '\0');
	break;
    case 'd':		/* double free of malloc'ed region */
	free(e);
	free(e);
	break;
    case 'f':		/* free of a pointer within an allocated region */
	free(e+1);
	break;
    case 'm':		/* unlimited heap memory allocation */
	while (malloc(SIZE)) ;
	break;
    case 'o':		/* buffer overrun */
	e[SIZE]=42;
	break;
    case 'p':		/* print the pointers */
	printf("a = %p\nb = %p\nc = %p\nd = %p\ne = %p\n", a, b, c, d, e);
    	break;
    case 'r':		/* unlimited stack memory allocation */
	foo(w, n);
	break;
    case 's':		/* freeing stack memory */
	free(d);
	break;
    case 'u':		/* buffer underrun */
	e[-1]=42;
	break;
    case 'w':		/* wait before returning */
	(void) getchar();
	break;
    case 'x':		/* assignment to read-only string */
	b[0] = 'H';
	break;
    case 'h':		/* smash the stack */
	e = c;
	memset(e, 42, 2*SIZE);
	break;
    default:
	printf("ignoring unknown option '%c'\n", w);
	break;
    }
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
	for (int j = 0; argv[i][j]; j++) {
	    foo(argv[i][j], SIZE);
	}
    }
    return EXIT_SUCCESS;
}
