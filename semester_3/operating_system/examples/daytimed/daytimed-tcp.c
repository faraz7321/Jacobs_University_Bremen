/*
 * daytimed/daytimed-tcp.c --
 *
 * A simple TCP over IPv4/IPv6 daytime server. The server waits for
 * incoming connections, sends a daytime string as a reaction to
 * successful connection establishment and finally closes the
 * connection down again.
 */

#define _POSIX_C_SOURCE 200809L
#define _DARWIN_C_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "tcp.h"

static const char *progname = "daytimed";

/*
 * Store the current date and time of the day using the local timezone
 * in the given buffer of the indicated size. Set the buffer to a zero
 * length string in case of errors.
 */

static size_t
strdaytime(char *buffer, size_t size)
{
    time_t ticks;
    struct tm *tm;

    ticks = time(NULL);
    tm = localtime(&ticks);
    if (tm == NULL) {
        buffer[0] = '\0';
        syslog(LOG_ERR, "localtime failed");
	return 0;
    }
    return strftime(buffer, size, "%F %T\r\n", tm);
}

/*
 * Implement the daytime protocol, loosely modeled after RFC 867.  Get
 * the current time, convert it into a struct tm and render it
 * according to the local timezone. Send the resulting string to the
 * client.
 */

static void
daytime(int cfd)
{
    size_t n;
    char message[128];

    n = strdaytime(message, sizeof(message));
    if (n == 0) {
	return;
    }

    n = tcp_write(cfd, message, strlen(message));
    if (n != strlen(message)) {
        syslog(LOG_ERR, "write failed");
	return;
    }
}

int
main(int argc, char *argv[])
{
    int tfd;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s port\n", progname);
        exit(EXIT_FAILURE);
    }

    (void) daemon(0, 0);

    openlog(progname, LOG_PID, LOG_DAEMON);

    tfd = tcp_listen(NULL, argv[1]);

    while (tfd != -1) {
	int cfd = tcp_accept(tfd);
	if (cfd == -1) {
	    close(tfd);
	    tfd = -1;
	}
        daytime(cfd);
	tcp_close(cfd);
    }

    tcp_close(tfd);

    closelog();

    return EXIT_SUCCESS;
}
