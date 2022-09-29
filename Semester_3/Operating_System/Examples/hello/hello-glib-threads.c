/*
 * hello-glib-threads.c --
 *
 *	This program uses the glib library to print a short message
 *      using two threads.
 */

#include <stdlib.h>
#include <glib.h>

static gpointer foo(gpointer data)
{
    const gchar *msg = (gchar *) data;
    
    g_assert(msg)
    g_print("%s\n", msg);

    return NULL;
}

int main(int argc, char *argv[])
{
    GThread *hello, *world;

    hello = g_thread_new(NULL, foo, "Hello ");
    world = g_thread_new(NULL, foo, "World\n");

    (void) g_thread_join(hello);
    (void) g_thread_join(world);

    return EXIT_SUCCESS;
}
