/*
 * hello-🌐.c --
 *
 *      This program uses the stdio library to print a short message,
 *      demonstrating that using unicode is feasible these days (with
 *      some compilers and tool chains, but note that cmake 3.23.5
 *      does not allow 'wild' characters in target names).
 */

#include <stdio.h>

void 🐜(void)
{
    char *📖 = "👋 🌎";
    puts(📖);
}

int main(void)
{
    🐜();
    return 0;
}
