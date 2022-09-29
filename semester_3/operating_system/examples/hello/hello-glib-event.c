/*
 * hello-glib-event.c --
 *
 *	This program uses the glib library to print a short message
 *      from an event loop.
 */

#include <stdlib.h>
#include <glib.h>

static gboolean foo(gpointer notused)
{
    const gchar msg[] = "Hello World";

    (void) notused;
    
    g_print("%s\n", msg);

    return G_SOURCE_CONTINUE;
}

static gboolean bar(gpointer user_data)
{
    GMainLoop *main_loop = (GMainLoop *) user_data;

    g_assert(main_loop);
    g_main_loop_quit(main_loop);
    return G_SOURCE_REMOVE;
}

int main(void)
{
    GMainLoop *main_loop;

    main_loop = g_main_loop_new(NULL, 0);
    if (! main_loop) {
        return EXIT_FAILURE;
    }

    g_timeout_add(10, foo, NULL);
    g_timeout_add(15, bar, main_loop);
    g_main_loop_run(main_loop);

    return EXIT_SUCCESS;
}
