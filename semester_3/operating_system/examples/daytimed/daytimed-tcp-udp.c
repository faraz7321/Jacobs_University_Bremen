/*
 * daytimed/daytimed-tcp-udp.c --
 *
 * A simple UDP and TCP over IPv4/IPv6 daytime server. The server
 * waits for incoming messages and sends a daytime string as a
 * reaction to received message. This version uses select() to handle
 * incoming TCP and UDP requests.
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
#include <sys/select.h>
#include <netdb.h>

#include "tcp.h"
#include "udp.h"

static const char *progname = "daytimed";

#ifndef NI_MAXHOST
#define NI_MAXHOST      1025
#endif
#ifndef NI_MAXSERV
#define NI_MAXSERV      32
#endif

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
daytime_udp(int fd)
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

/*
 * Implement the daytime protocol, loosely modeled after RFC 867.  Get
 * the current time, convert it into a struct tm and render it
 * according to the local timezone. Send the resulting string to the
 * client.
 */

static void
daytime_tcp(int cfd)
{
    size_t n;
    time_t ticks;
    struct tm *tm;
    char message[128];

    ticks = time(NULL);
    tm = localtime(&ticks);
    if (tm == NULL) {
        syslog(LOG_ERR, "localtime failed");
        return;
    }
    (void) strftime(message, sizeof(message), "%F %T\r\n", tm);

    n = tcp_write(cfd, message, strlen(message));
    if (n != strlen(message)) {
        syslog(LOG_ERR, "write failed");
	return;
    }
}

int
main(int argc, char *argv[])
{
    int tfd, ufd;
    fd_set fdset;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s port\n", progname);
        exit(EXIT_FAILURE);
    }

    (void) daemon(0, 0);

    openlog(progname, LOG_PID, LOG_DAEMON);

    ufd = udp_open(NULL, argv[1]);
    tfd = tcp_listen(NULL, argv[1]);
    
    while (ufd != -1 || tfd != -1) {

        FD_ZERO(&fdset);
        if (ufd > -1) FD_SET(ufd, &fdset);
        if (tfd > -1) FD_SET(tfd, &fdset);

        if (select(1 + (ufd > tfd ? ufd : tfd),
                   &fdset, NULL, NULL, NULL) == -1) {
            syslog(LOG_ERR, "select failed: %s", strerror(errno));
            return EXIT_FAILURE;
        }

        if (tfd > -1 && FD_ISSET(tfd, &fdset)) {
	    int cfd = tcp_accept(tfd);
	    if (cfd == -1) {
		close(tfd);
		tfd = -1;
	    }
	    daytime_tcp(cfd);
	    tcp_close(cfd);
        }
        if (ufd > -1 && FD_ISSET(ufd, &fdset)) {
            ufd = daytime_udp(ufd);
        }
    }

    if (ufd != -1) udp_close(ufd);
    if (tfd != -1) tcp_close(tfd);

    closelog();

    return EXIT_SUCCESS;
}
