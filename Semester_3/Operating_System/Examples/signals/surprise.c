/*
 * signals/surprise.c --
 *
 *	Depending on your system, you might see that signals interrupt
 *	even simple assignments. The alarm() call arranges for a
 *	SIGALRM to be delivered to the calling process after a number
 *	of seconds. Compile without optimizations to see the effect.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>

typedef struct twins { int64_t a, b; } twins_t;
static const twins_t zeros = { 0, 0 }, ones = { 1, 1 };
static twins_t twins;
static volatile sig_atomic_t go_on = 1;

static void handler(int signum)
{
    if (signum == SIGALRM) {
        go_on = (twins.a == twins.b);
        if (go_on) {
            (void) alarm(1);                        /* request next alarm */
        } else {
            printf("twins = {%" PRId64 ",%" PRId64 "}\n", twins.a, twins.b);
        }
    }
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }
    
    (void) alarm(1);                            /* request first alarm */
    while (go_on) {
        twins = zeros;
	twins = ones;
    }
    
    printf("twins = {%" PRId64 ",%" PRId64 "}\n", twins.a, twins.b);
    return EXIT_SUCCESS;
}
