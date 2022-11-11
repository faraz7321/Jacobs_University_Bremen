/*
 * msh/job.c --
 *
 * This file implements all msh functions which manipulate background
 * jobs running under msh control.
 */

#define _POSIX_C_SOURCE 201112L

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

#include "msh.h"

msh_job_t*
msh_job_create(msh_interp_t *msh, const char *cmd)
{
    msh_job_t *job;
    slist_t *elem;
    int i;

    assert(msh);

    job = msh_malloc(sizeof(msh_job_t));

    for (i = 1; 1; i++) {
	for (elem = msh->jobs; elem; elem = slist_next(elem)) {
	    msh_job_t *j = (msh_job_t *) slist_data(elem);
	    if (i == j->num) break;
	}
	if (! elem) break;
    }
    job->num = i;
    job->status = MSH_JOB_STATUS_INIT;
    job->interp = msh;
    job->cmd = msh_strdup(cmd);
    msh->jobs = slist_append(msh->jobs, job);
    return job;
}

void
msh_job_delete(msh_job_t *job)
{
    assert(job);

    if (job->interp) {
	job->interp->jobs = slist_remove(job->interp->jobs, job);
    }
    if (job->cmd) {
	free(job->cmd);
    }
    free(job);
}

void
msh_job_run(msh_job_t *job, pid_t pid)
{
    assert(job);

    job->pid = pid;
    job->status = MSH_JOB_STATUS_RUN;
}

void
msh_job_term(msh_job_t *job)
{
    assert(job);

    job->status = MSH_JOB_STATUS_TERM;
    msh_job_delete(job);
}

void
msh_job_kill(msh_job_t *job)
{
    assert(job);

    kill(job->pid, SIGTERM);
}

const char*
msh_job_strstatus(msh_job_t *job)
{
    assert(job);

    switch (job->status) {
    case MSH_JOB_STATUS_INIT:
	return "initializing";
	break;
    case MSH_JOB_STATUS_RUN:
	return "running";
	break;
    case MSH_JOB_STATUS_TERM:
	return "terminated";
	break;
    }
    assert(0);
}
