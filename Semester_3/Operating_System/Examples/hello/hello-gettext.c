/*
 * http://www.labri.fr/perso/fleury/posts/programming/a-quick-gettext-tutorial.html
 *
 * Directory tree layout:
 *
 * hello/
 *  |-- fr
 *  |    \-- LC_MESSAGES
 *  |         \-- hello.mo
 *  |-- hello.c
 *  |-- Makefile
 *  \-- po/
 *       |--hello.pot
 *       \-- fr/
 *            |-- hello.mo
 *            \-- hello.po
 *
 * Initial workflow:
 *
 *          xgettext                 msginit                   msgfmt
 * hello.c ----------> po/hello.pot ---------> po/fr/hello.po --------> po/fr/hello.m
 *
 * Update workflow:
 *
 *          xgettext -j                  msgmerge                   msgfmt
 * hello.c -------------> po/hello.pot -----------> po/fr/hello.po --------> po/fr/hello.mo
 *
 * ./hello
 * LANG=fr_FR.utf8 ./hello
 */

#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int
main(void)
{
    /* Setting the i18n environment */
    setlocale (LC_ALL, "");
#if 1
    bindtextdomain ("hello", getenv("PWD"));
#else
    bindtextdomain ("hello", "/usr/share/locale/");
#endif
    textdomain ("hello");
    
    /* Example of i18n usage */
    printf(_("Hello World\n"));
    
    return EXIT_SUCCESS;
}

