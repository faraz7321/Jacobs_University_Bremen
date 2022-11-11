/*
 * load.c --
 *
 *	Obtain and display the system load.
 */

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t keep_going = 1;

static void
catcher(int signum)
{
    (void) signum;

    keep_going = 0;
}

static double
getload()
{
    FILE *f;
    double load;
    int c;
    
    f = popen("uptime", "r");
    if (! f) {
	return -1;
    }

    /* linux */
    /*  19:06:48 up  2:53,  1 user,  load average: 0.15, 0.06, 0.03 */
    /* macos */
    /* 23:06  up 4 days, 12:42, 3 users, load averages: 1.01 0.76 0.67 */

    while ((c = fgetc(f)) != EOF) {
	switch (c) {
	case ':':
	    c = fgetc(f);
	    if (c == ' ') {
		if (fscanf(f, "%lf", &load) == 1) {
		    pclose(f);
		    return load;
		}
	    }
	    break;
	}
    }

    pclose(f);
    return -1;
}

int
main(void)
{
    double l;
    int i;
    
    signal(SIGINT, catcher);
    
    while (keep_going) {
	l = getload();
	if (l >= 0) {
	    printf("%5.2f ", l);
	    for (i = 0; i < l * 10; i++) {
		printf("%c", (i % 10) == 0 ? '|' : '-');
	    }
	}
	printf("\n");
	sleep(3);
    }
    
    return 0;
}
