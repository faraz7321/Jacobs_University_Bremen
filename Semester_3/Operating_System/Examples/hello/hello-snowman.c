/*
 * hello/hello-snowman.c --
 *
 * A hello world program using wide characters in order to greet a
 * snowman. To run it, you need to have a terminal capable of
 * interpreting UTF-8 and you have to set a suitable language
 * environment, e.g.,
 *
 * LANG=C.UTF-8 ./hello-snowman.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include <locale.h>

int
main()
{
    setlocale(LC_CTYPE, "");
    fwprintf(stdout, L"안, 蠀, ☃\n");
    return EXIT_SUCCESS;
}
