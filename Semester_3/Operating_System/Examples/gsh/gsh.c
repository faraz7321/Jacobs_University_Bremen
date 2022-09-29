/*
 * gsh/gsh.c --
 *
 *	A simple stupid shell using glib abstractions.
 */

#include <stdlib.h>
#include <unistd.h>
#include <glib.h>

static gboolean
execute(gchar *command_line, GError **err)
{
    GError *tmp_error = NULL;
    gint exit_status, argc;
    gchar **argv;

    g_return_val_if_fail(err == NULL || *err == NULL, FALSE);

    g_shell_parse_argv(command_line, &argc, &argv, &tmp_error);
    if (tmp_error) {
        g_propagate_error(err, tmp_error);
	return FALSE;
    }

    g_spawn_sync(NULL, argv, NULL, 
		 G_SPAWN_SEARCH_PATH | G_SPAWN_CHILD_INHERITS_STDIN,
		 NULL, NULL, NULL, NULL, &exit_status, &tmp_error);
    if (tmp_error) {
        g_propagate_error(err, tmp_error);
	return FALSE;
    }

    return TRUE;
}

int main(void)
{
    GIOChannel *gio;
    GError *error = NULL;
    gboolean keep_going = TRUE;

    g_set_prgname("gsh");

    gio = g_io_channel_unix_new(STDIN_FILENO);
    if (! gio) {
        g_printerr("%s: failed to setup input channel", g_get_prgname());
	exit(EXIT_FAILURE);
    }
 
    while (keep_going) {
        gchar *command_line;
	gsize command_line_length;
	GIOStatus status;
	
	g_clear_error(&error);
	g_print("%s > ", g_get_prgname());
	status = g_io_channel_read_line(gio, &command_line, 
					&command_line_length, NULL, &error);
	if (error) {
  	    g_printerr("%s: %s\n", g_get_prgname(), error->message);
	    continue;
	}

	switch (status) {
	case G_IO_STATUS_ERROR:
	    continue;
	case G_IO_STATUS_NORMAL:
	    if (command_line_length) {
	      execute(command_line, &error);
	      if (error) {
		  g_printerr("%s: %s\n", g_get_prgname(), error->message);
		}
	    }
	    break;
	case G_IO_STATUS_EOF:
	    keep_going = FALSE;
	    continue;
	case G_IO_STATUS_AGAIN:
	    continue;
	}
    }
    g_clear_error(&error);
    
    return EXIT_SUCCESS;
}
