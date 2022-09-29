/*
 * hello-atexit.c --
 *
 *	This file contains a program which uses the stdio library to
 *      print a short messages just before the process terminates.
 *      Note that atexit handlers are called in reverse order and
 *      there are limits on the number of exit handlers that can be
 *      installed.
 */

#include <stdlib.h>
#include <stdio.h>

static void foo(void)
{
    (void) fputs("Hello ", stdout);
}

static void bar(void)
{
    (void) puts("World");
}

int main(void)
{
    return (atexit(bar) || atexit(foo));
}
