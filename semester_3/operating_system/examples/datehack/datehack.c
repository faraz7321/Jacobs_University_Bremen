/*
 * datehack/datehack.c --
 *
 * gcc -Wall -fPIC -DPIC -c datehack.c
 * ld -shared -o datehack.so datehack.o -ldl (Linux)
 * ld -dylib -o datehack.dylib datehack.o -ldl (MacOS)
 *
 * LD_PRELOAD=./datehack.so date (Linux)
 * DYLD_INSERT_LIBRARIES=./datehack.dylib date (MacOS)
 *
 * See fakeroot <http://freecode.com/projects/fakeroot> for a project
 * making use of LD_PRELOAD for good reasons.
 * 
 * http://hackerboss.com/overriding-system-functions-for-fun-and-profit/
 */

#define _GNU_SOURCE
#include <time.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

static struct tm *(*orig_localtime)(const time_t *timep);
static int (*orig_clock_gettime)(clockid_t clk_id, struct timespec *tp);

struct tm *localtime(const time_t *timep)
{
    time_t t = *timep - 60 * 60 * 24;
    return orig_localtime(&t);
}

int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    int rc = orig_clock_gettime(clk_id, tp);
    if (tp) {
        tp->tv_sec -= 60 * 60 * 24;
    }
    return rc;
}

__attribute__ ((constructor))
static void _init(void)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
    orig_localtime = dlsym(RTLD_NEXT, "localtime");
    if (! orig_localtime) {
	abort();
    }

    orig_clock_gettime = dlsym(RTLD_NEXT, "clock_gettime");
    if (! orig_clock_gettime) {
        abort();
    }
#pragma GCC diagnostic pop
}
