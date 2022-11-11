/*
 * msh/cmd.c --
 *
 * This file implements all msh buildin commands. It also exports an
 * array describing all build-in commands so that they can be called
 * by the msh interpreter.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "msh.h"

int
msh_cd(msh_interp_t *msh, int argc, char **argv)
{
    const char *path;
    
    assert(msh && argv);

    if (argc > 2) {
        fprintf(stderr, "usage: %s [path]\n", argv[0]);
        return 1;
    }

    if (argc == 1) {
        path = msh_home();
        if (! path) {
            fprintf(stderr, "%s: %s: no home\n", progname, argv[0]);
            return 1;
        }
    } else {
        path = argv[1];
    }
    
    if (chdir(path) == -1) {
        fprintf(stderr, "%s: %s: %s: %s\n",
                progname, argv[0], path, strerror(errno));
        return 1;
    }
    return 0;
}

int
msh_eval(msh_interp_t *msh, int argc, char **argv)
{
    size_t size = 0;
    char *cmd, *p;
    int i, code;
    
    assert(msh && argv);

    if (argc < 2) return 0;

    for (i = 1; i < argc; i++) {
        size += strlen(argv[i]) + 2;
    }
    cmd = msh_malloc(size);
    for (i = 1, p = cmd; i < argc; i++) {
        if (i > 1) *p++ = ' ';
        strcpy(p, argv[i]);
        p += strlen(argv[i]);
    }
    code = msh_interp_eval(msh, cmd);
    free(cmd);
    return code;
}

int
msh_exec(msh_interp_t *msh, int argc, char **argv)
{
    assert(msh && argv);

    if (argc == 1) {
        fprintf(stderr, "usage: %s path ...\n", argv[0]);
        return 1;
    }

    execvp(argv[1], argv+1);
    fprintf(stderr, "%s: %s: %s: %s\n",
            progname, argv[0], argv[1], strerror(errno));
    return 1;
}

int
msh_exit(msh_interp_t *msh, int argc, char **argv)
{
    char *p;
    int code;

    assert(msh && argv);

    if (argc > 2) {
        fprintf(stderr, "usage: %s [n]\n", argv[0]);
        return 1;
    }

    code = msh->code;
    if (argc == 2) {
        code = strtol(argv[1], &p, 0);
        if (*p != '\0' || code < 0) {
            fprintf(stderr, "%s: %s: %s: invalid exit code\n",
                    progname, argv[0], argv[1]);
            return 1;
        }
    }
    exit(code);
}

static void
print_job(void *data, void *user)
{
    (void) user;
    msh_job_t *job = (msh_job_t *) data;

    printf("[%d] %d %12s %s\n", job->num, job->pid,
           msh_job_strstatus(job), job->cmd ? job->cmd : "");
}

static int
job_cmp_pid(void *data, void *pattern)
{
    msh_job_t *job = (msh_job_t *) data;
    int *num = (int *) pattern;

    if (*num == job->pid) {
        return 0;
    }
    if (*num < job->pid) {
        return -1;
    } else {
        return 1;
    }
}

int
msh_jobs(msh_interp_t *msh, int argc, char **argv)
{
    slist_t *elem;
    char *p;
    int n;
    
    assert(msh);

    if (argc == 1) {
        slist_foreach(msh->jobs, print_job, NULL);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        n = strtol(argv[i], &p, 0);
        if (*p != '\0') {
            fprintf(stderr, "%s: %s: %s: no such job\n",
                    progname, argv[0], argv[i]);
            continue;
        }
        elem = slist_search(msh->jobs, job_cmp_pid, &n);
        if (elem) {
            print_job(slist_data(elem), NULL);
        } else {
            printf("%s: %s: %s: no such job\n",
                   progname, argv[0], argv[i]);
        }
    }
    return 0;
}

int
msh_pwd(msh_interp_t *msh, int argc, char **argv)
{
    char *p, *q;
    size_t size = 256;
    
    assert(msh && argv);

    if (argc != 1) {
        fprintf(stderr, "usage: %s\n", argv[0]);
        return 1;
    }

    p = msh_malloc(size);
    while (1) {
        q = getcwd(p, size);
        if (q) break;
        if (errno != ERANGE) {
            break;
        }
        size *= 2;
        p = msh_realloc(p, size);
    }

    if (q) {
        printf("%s\n", p);
    } else {
        fprintf(stderr, "%s: %s: %s\n",
                progname, argv[0], strerror(errno));
    }
    free(p);
    return (q != 0);
}

static int
cmp_trap(void *data, void *pattern)
{
    msh_trap_t *trap = (msh_trap_t *) data;
    int *num = (int *) pattern;

    if (*num == trap->signum) {
        return 0;
    }
    if (*num < trap->signum) {
        return -1;
    } else {
        return 1;
    }
}

static void
msh_signal_handler(int signum)
{
    slist_t *elem;
    
    if (! msh_trap_interp) {
        return;
    }

    elem = slist_search(msh_trap_list, cmp_trap, &signum);
    if (elem) {
        msh_trap_t *trap = (msh_trap_t *) slist_data(elem);
        if (trap->cmd) {
            msh_interp_eval(msh_trap_interp, trap->cmd);
        }
    }
}

/*
 * The syntax of the command is as follows:
 *
 * trap [cmd] [signum ...]
 *
 * A cmd is present if it is not a number. There are some special
 * cases:
 *
 * (a) no arguments:    list all defined trap commands
 * (b) no cmd argument: install default signal handler
 * (c) cmd == "-":      install default signal handler
 * (d) zero length cmd: install ignore signal handler
 * (e) cmd == ":":      install ignore signal handler
 *
 * This syntax really sucks.
 */

int
msh_trap(msh_interp_t *msh, int argc, char **argv)
{
    slist_t *elem;
    msh_trap_t *trap;
    int i, signum, sigindex = 2;
    struct sigaction sa;
    char *p;

    assert(msh);
    
    if (argc == 1) {
        for (elem = msh_trap_list; elem; elem = slist_next(elem)) {
            trap = (msh_trap_t *) slist_data(elem);
            printf("%d:\t%s\n", trap->signum, trap->cmd);
        }
        return 0;
    }

    sa.sa_handler = msh_signal_handler;
    sa.sa_flags = 0;

    signum = strtol(argv[1], &p, 0);
    if (*p == '\0') {
        sigindex = 1;
    }
    if (*p == '\0' || strcmp(argv[1], "-") == 0) {
        sa.sa_handler = SIG_DFL;
    }
    if (strlen(argv[1]) == 0 || strcmp(argv[1], ":") == 0) {
        sa.sa_handler = SIG_IGN;
    }

    for (i = sigindex; i < argc; i++) {
        signum = strtol(argv[i], &p, 0);
        if (*p != '\0' || signum <= 0) {
            fprintf(stderr, "%s: %s: %s: invalid signal number\n",
                    progname, argv[0], argv[1]);
            return 1;
        }
        elem = slist_search(msh_trap_list, cmp_trap, &signum);
        if (elem) {
            trap = (msh_trap_t *) slist_data(elem);
            if (sa.sa_handler == msh_signal_handler) {
                if (trap->cmd) free(trap->cmd);
                trap->cmd = msh_strdup(argv[1]);
            } else {
                free(trap);
                msh_trap_list = slist_remove(msh_trap_list, trap);
            }
        } else {
            if (sa.sa_handler == msh_signal_handler) {
                trap = msh_malloc(sizeof(msh_trap_t));
                trap->signum = signum;
                trap->cmd = msh_strdup(argv[1]);
                msh_trap_list = slist_append(msh_trap_list, trap);
            }
        }
        if (sigaction(signum, &sa, NULL) == -1) {
            fprintf(stderr, "%s: %s: %s: %s\n",
                    progname, argv[0], argv[i], strerror(errno));
            return 1;
        }
    }

    return 0;
}

int
msh_wait(msh_interp_t *msh, int argc, char **argv)
{
    slist_t *elem;
    char *p;
    int n, code;
    pid_t pid;

    assert(msh);

    if (argc == 1) {

	/* Wait for all jobs associated with this interpreter. Do not
	 * use waitpid(-1, NULL, 0) since we do not want to wait for
	 * jobs associated with other interpreters. */
	
      restart:
	for (elem = msh->jobs; elem; elem = slist_next(elem)) {
	    msh_job_t *job = (msh_job_t *) slist_data(elem);
	    pid = waitpid(job->pid, NULL, 0);
	    if (pid == -1) {
		fprintf(stderr, "%s: %s: wait failed: %s\n",
			progname, argv[0], strerror(errno));
		return 1;
	    }
	    if (pid > 0) {
		msh_job_term(job);
		goto restart;
	    }
	}
	return 0;
    }

    for (int i = 1; i < argc; i++) {
        n = strtol(argv[i], &p, 0);
        if (*p != '\0') {
            fprintf(stderr, "%s: %s: %s: invalid process number\n",
                    progname, argv[0], argv[1]);
            return 1;
        }
        elem = slist_search(msh->jobs, job_cmp_pid, &n);
        if (! elem) {
            fprintf(stderr, "%s: %s: %s: unknown process number\n",
                    progname, argv[0], argv[1]);
        } else {
            msh_job_t *job = (msh_job_t *) slist_data(elem);
            pid = waitpid(job->pid, &code, 0);
            if (pid == -1) {
                fprintf(stderr, "%s: %s: wait failed: %s\n",
                        progname, argv[0], strerror(errno));
                continue;
            }
            if (pid > 0) {
                msh_job_term(job);
            }
        }
    }

    return WEXITSTATUS(code);
}

msh_cmd_t msh_cmds[] = {
    { "cd",     msh_cd },
    { "eval",   msh_eval },
    { "exec",   msh_exec },
    { "exit",   msh_exit },
    { "jobs",   msh_jobs },
    { "pwd",    msh_pwd },
    { "trap",   msh_trap },
    { "wait",   msh_wait },
    { NULL, NULL },
};
