/*
 * msh/interp.c --
 *
 * This file implements the core of the msh interpreter, which is
 * basically the tokenizer and the execution of build-in commands
 * or external commands.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#include "msh.h"

msh_interp_t*
msh_interp_create()
{
    msh_interp_t *msh;
    size_t size;

    msh = msh_malloc(sizeof(msh_interp_t));
    memset(msh, 0, sizeof(msh_interp_t));

    size = strlen(progname) + 4;
    msh->prompt = msh_malloc(size);
    snprintf(msh->prompt, size, "%s > ", progname);

    if (! msh_trap_interp) {
	msh_trap_interp = msh;
    }

    return msh;
}

void
msh_interp_delete(msh_interp_t *msh)
{
    slist_t *elem;

    assert(msh);

    if (msh_trap_interp == msh) {
	msh_trap_interp = NULL;
    }

    for (elem = msh->jobs; elem; elem = slist_next(elem)) {
	msh_job_t *job = (msh_job_t *) slist_data(elem);
	msh_job_kill(job);
    }

    if (msh->prompt) free(msh->prompt);
    free(msh);
}

static int
tokenize(char *str, int *argc, char **argv[])
{
    int n;
    char *p;

    assert(str && argc && argv);

    /* Estimate the size of the argv vector. */
    for (n = 2, p = str; *p; p++) {
	if (*p == ' ' || *p == '\t') n++;
    }

    *argv = msh_malloc(n * sizeof(char*));
    for (*argc = 0, p = strtok(str, " \t");
	 p; p = strtok(NULL, " \t"), (*argc)++) {
	(*argv)[*argc] = p;
    }
    (*argv)[*argc] = NULL;
    return 0;
}

static int
exec_buildin(msh_interp_t *msh, int argc, char **argv, msh_job_t *job)
{
    pid_t pid;
    int i;

    assert(msh && argv);

    for (i = 0; msh_cmds[i].name; i++) {
	if (strcmp(msh_cmds[i].name, argv[0]) == 0) {
	    break;
	}
    }

    if (! msh_cmds[i].name) {
	return -1;
    }
    
    if (! job) {
	return msh_cmds[i].handler(msh, argc, argv);
    }
    
    pid = fork();
    if (pid == -1) {
	perror(progname);
	return -1;
    }
    if (pid == 0) {			/* child */
	exit(msh_cmds[i].handler(msh, argc, argv));
    } else {				/* parent */
	msh_job_run(job, pid);
	printf("[%d] %d\n", job->num, job->pid);
    }
    return 0;
}

static int
exec_process(msh_interp_t *msh, int argc, char **argv, msh_job_t *job)
{
    pid_t pid;
    int code = 0;

    (void) argc;
    assert(msh && argv);

    pid = fork();
    if (pid == -1) {
	perror(progname);
	return -1;
    }
    if (pid == 0) {			/* child */
	execvp(argv[0], argv);
	fprintf(stderr, "%s: %s: %s\n",
		progname, argv[0], strerror(errno));
	_exit(EXIT_FAILURE);
    } else {				/* parent */
	if (! job) {
	    waitpid(pid, &code, 0);
	} else {
	    msh_job_run(job, pid);
	    printf("[%d] %d\n", job->num, job->pid);
	}
	return code;
    }
}

int
msh_interp_evalv(msh_interp_t *msh, int argc, char **argv)
{
    msh_job_t *job = NULL;
    int code;
    
    if (strcmp(argv[argc-1], "&") == 0) {
	argv[argc-1] = NULL;
	argc--;
	job = msh_job_create(msh, argv[0]);
    }

    code = exec_buildin(msh, argc, argv, job);
    if (code == -1) {
	code = exec_process(msh, argc, argv, job);
    }
    msh->code = code;
    return code;
}

int
msh_interp_eval(msh_interp_t *msh, const char *string)
{
    char *cmd, **argv = NULL;
    int argc, code;

    assert(string);

    cmd = msh_strdup(string);
    if (tokenize(cmd, &argc, &argv) == -1) {
	printf("%s: failed to tokenize command\n", progname);
	return 1;
    } else {
	code = msh_interp_evalv(msh, argc, argv);
	free(argv);
    }
    free(cmd);
    return code;
}

void
msh_interp_reap(msh_interp_t *msh)
{
    slist_t *elem;
    pid_t pid;

    assert(msh);

    /* Check whether any jobs associated with this interpreter have
     * completed. Do not use waitpid(-1, NULL, WNOHANG) since we do
     * not want to check for jobs associated with other interpreters. */

  restart:
    for (elem = msh->jobs; elem; elem = slist_next(elem)) {
	msh_job_t *job = (msh_job_t *) slist_data(elem);
	pid = waitpid(job->pid, NULL, WNOHANG);
	if (pid == -1) {
	    fprintf(stderr, "%s: wait failed: %s\n",
		    progname, strerror(errno));
	    continue;
	}
	if (pid > 0) {
	    printf("[%d] %d terminated %s\n", job->num, job->pid, job->cmd);
	    msh_job_term(job);
	    goto restart;
	}
    }

    fflush(stdout);
}
