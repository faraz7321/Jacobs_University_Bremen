/*
 * hello-glib.c --
 *
 *	This program uses the glib library to print a short message.
 *	The glib library provides an abstraction layer above the C
 *	library and offers increased portability (Unix, Windows,
 *	MacOS), lots of powerful data types, and useful abstractions
 *	(like thread pools, event loops, and a complete object system)
 *	for building applications.
 *
 *      This example demonstrates how a print handler function can be
 *      installed to handle all the g_print() messages for the
 *      standard output (and to determine any failures). (The default
 *      print handler uses libc's FILE streams but that is only
 *      obvious when you read the source).
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

static int exit_code = EXIT_SUCCESS;

static void print_handler(const gchar *msg)
{
    ssize_t n;
    size_t len;

    len = strlen(msg);
    n = write(STDOUT_FILENO, msg, len);
    if (n == -1 || (size_t) n != len) {
        exit_code = EXIT_FAILURE;
    }
}

int main(void)
{
    const gchar msg[] = "Hello World";
    
    g_set_print_handler(print_handler);
    g_print("%s\n", msg);

    return exit_code;
}
