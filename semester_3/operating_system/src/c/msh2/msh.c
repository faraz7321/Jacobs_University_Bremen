/*
 * msh/msh.c --
 *
 * This file implements a simple shell called msh. It uses GNU
 * readline and history libraries and supports background processes,
 * input/output redirection and a set of build in commands.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "msh.h"

/*
 * Global variables we can not avoid:
 */

const char *progname = "msh";

slist_t *msh_trap_list = NULL;
msh_interp_t *msh_trap_interp = NULL;

static int
mainloop(msh_interp_t *msh)
{
    char *cmd;
    int code = 0;

    assert(msh);

    while (1) {
	cmd = readline(msh->prompt ? msh->prompt : "> ");
	msh_interp_reap(msh);
        if (cmd == NULL) {
            break;
        }
        if (strlen(cmd) == 0) {
            free(cmd);
	    continue;
        }
	add_history(cmd);
	code = msh_interp_eval(msh, cmd);
    }
    return code;
}

int
main(int argc, char *argv[])
{
    int history_file_size = 1000;	/* arbitrary choice */
    const char *histfilesize = getenv("HISTFILESIZE");
    char *path = NULL;
    const char *home;
    char *cmd = NULL;
    msh_interp_t *msh;
    int c, code;

    while ((c = getopt(argc, argv, "c:v")) >= 0) {
	switch (c) {
	case 'c':
	    cmd = optarg;
	    break;
	case 'v':
	    break;
	default:
	    fprintf(stderr, "usage: %s [-c cmd] [-v] [script] ...\n", progname);
	    exit(EXIT_FAILURE);
	}
    }

    /*
     * Execute a single command and we are done.
     */

    if (cmd) {
	msh = msh_interp_create();
	code = msh_interp_eval(msh, cmd);
	msh_interp_delete(msh);
	return code;
    }

    /* Initialize readline and history support and compute a suitable
     * path for the history file. */
    rl_readline_name = (char *) progname;
    using_history();
    if ((home = msh_home())) {
	size_t size = strlen(home)+strlen(progname)+42;
	path = msh_malloc(size);
	snprintf(path, size, "%s/.%s_history", home, progname);
    }
    read_history(path);

    /* We are ready now to run the shell... */
    
    msh = msh_interp_create();
    code = mainloop(msh);
    msh_interp_delete(msh);

    /* Write back the history file. */
    if (histfilesize) {
	char *p;
	int n;
	n = strtol(histfilesize, &p, 0);
	if (*p == '\0') {
	    history_file_size = n;
	}
    }
    stifle_history(history_file_size);
    if (write_history(path) != 0) {
	fprintf(stderr, "%s: writing history failed\n", progname);
    }
    free(path);

    return code;
}
