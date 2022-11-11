/*
 * daytimed/daytimed-udp.c --
 *
 * A simple UDP over IPv4/IPv6 daytime server. The server waits for
 * incoming messages and sends a daytime string as a reaction to
 * received message.
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

#include "udp.h"

#ifndef NI_MAXHOST
#define NI_MAXHOST      1025
#endif
#ifndef NI_MAXSERV
#define NI_MAXSERV      32
#endif

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
 * Implement the daytime protocol, loosely modeled after RFC 867.
 */

static int
daytime(int fd)
{
    char message[128];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    struct sockaddr_storage from;
    socklen_t fromlen = sizeof(from);
    int n;

    n = recvfrom(fd, message, sizeof(message), 0,
                 (struct sockaddr *) &from, &fromlen);
    if (n == -1) {
        syslog(LOG_ERR, "recvfrom failed: %s", strerror(errno));
        return -1;
    }

    n = getnameinfo((struct sockaddr *) &from, fromlen,
                    host, sizeof(host), serv, sizeof(serv),
                    NI_NUMERICHOST | NI_DGRAM);
    if (n) {
        syslog(LOG_ERR, "getnameinfo failed: %s", gai_strerror(n));
    } else {
        syslog(LOG_DEBUG, "request from %s%s%s:%s",
	       strchr(host, ':') == NULL ? "" : "[",
	       host,
	       strchr(host, ':') == NULL ? "" : "]",
	       serv);
    }

    if (strdaytime(message, sizeof(message))) {
	n = sendto(fd, message, strlen(message), 0,
		   (struct sockaddr *) &from, fromlen);
	if (n == -1) {
	    syslog(LOG_ERR, "sendto failed: %s", strerror(errno));
	}
    }

    return fd;
}

int
main(int argc, char *argv[])
{
    int ufd;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s port\n", progname);
        exit(EXIT_FAILURE);
    }

    (void) daemon(0, 0);

    openlog(progname, LOG_PID, LOG_DAEMON);

    ufd = udp_open(NULL, argv[1]);

    while (ufd != -1) {
        ufd = daytime(ufd);
    }

    udp_close(ufd);

    closelog();

    return EXIT_SUCCESS;
}
