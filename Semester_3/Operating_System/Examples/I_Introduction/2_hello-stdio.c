/*
 * hello-stdio.c --
 *
 * This program uses the stdio library to print a short message.
 * Note that we check the return code of puts() and that
 * we flush() the buffered output stream manually to check
 * whether writing to stdout actually worked.
 *
 * Exercise:
 *
 * On Linux, run the program with ltrace and strace. Explain the
 * output produced by ltrace and strace.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const char msg[] = "Hello World";
    int n;

    n = puts(msg);
    if (n == EOF)
    {
        perror("puts");
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF)
    {
        perror("fflush");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}