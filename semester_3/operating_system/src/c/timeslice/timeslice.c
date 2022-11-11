/*
 * timeslice/timeslice.c --
 *
 *	Print the timeslice used by the Linux round-robin
 *	scheduler. This program is not portable.
 */

#define _POSIX_C_SOURCE 201112L

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>

int
main(void)
{
    struct timespec t;
    int r;
    
    r = sched_rr_get_interval(getpid(), &t);
    if (r < 0) {
	perror("sched_rr_get_interval");
	return 1;
    }
    printf("timeslice: %ld.%09ld seconds\n", t.tv_sec, t.tv_nsec);

    return 0;
}
