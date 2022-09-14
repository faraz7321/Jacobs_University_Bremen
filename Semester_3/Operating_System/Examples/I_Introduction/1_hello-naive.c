/*
 * hello-naive.c --
 *
 * This program uses the stdio library to print a short message.
 *
 * Exercise:
 *
 * On Linux, run the program with ltrace and strace. Explain the
 * output produced by ltrace and strace.
 */
#include <stdio.h>

int main(void)
{
    printf("Hello World\n");
    return 0;
}