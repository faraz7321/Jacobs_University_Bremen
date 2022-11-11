/*
 * msh/msh.h --
 *
 * Definitions for the simple shell msh.
 */

#ifndef _MSH_H
#define _MSH_H

#include <sys/types.h>

#include "slist.h"

extern const char *progname;

/*
 * Structure to describe an msh shell interpreter:
 */

typedef struct {
    char    *prompt;		/* current prompt string */
    int     code;		/* exit code of the last command */
    slist_t *jobs;		/* list of background jobs */
} msh_interp_t;

extern msh_interp_t*
msh_interp_create();

extern void
msh_interp_delete(msh_interp_t *msh);

extern int
msh_interp_eval(msh_interp_t *msh, const char *string);

extern int
msh_interp_evalv(msh_interp_t *msh, int argc, char **argv);

extern void
msh_interp_reap(msh_interp_t *msh);

/*
 * Structure to describe a build-in command:
 */

typedef struct {
    char *name;
    int (*handler)(msh_interp_t *msh, int argc, char **argv);
} msh_cmd_t;

extern msh_cmd_t msh_cmds[];

/*
 * Structure to describe a background command:
 */

#define MSH_JOB_STATUS_INIT	0x01
#define MSH_JOB_STATUS_RUN	0x02
#define MSH_JOB_STATUS_TERM	0x03

typedef struct {
    int   num;			/* unique small job number */
    pid_t pid;			/* process id (should be process group) */
    int   status;		/* job status, see defines above */
    char  *cmd;			/* cmd executed by the job (argv[0]) */
    msh_interp_t *interp;	/* msh interpreter running the job */
} msh_job_t;

extern msh_job_t*
msh_job_create(msh_interp_t *msh, const char *cmd);

extern void
msh_job_delete(msh_job_t *job);

extern void
msh_job_run(msh_job_t *job, pid_t pid);

extern void
msh_job_term(msh_job_t *job);

extern void
msh_job_kill(msh_job_t *job);

extern const char*
msh_job_strstatus(msh_job_t *job);

/*
 * Structure to describe installed signal handlers:
 */

typedef struct {
    int  signum;		/* signal number */
    char *cmd;			/* command to execute */
} msh_trap_t;

extern slist_t *msh_trap_list;		/* list of msh trap handlers */

extern msh_interp_t *msh_trap_interp;	/* interpreter used for signals */

/*
 * General utilities:
 */

void*
msh_malloc(size_t size);

void*
msh_realloc(void *ptr, size_t size);

char*
msh_strdup(const char *s);

const char*
msh_home();

#endif
