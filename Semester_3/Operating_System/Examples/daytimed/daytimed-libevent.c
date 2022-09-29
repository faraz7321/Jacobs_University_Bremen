/*
 * daytimed/daytimed-libevent.c --
 *
 * A simple UDP and TCP over IPv4/IPv6 daytime server. The server
 * waits for incoming messages and sends a daytime string as a
 * reaction to received message. This version uses libevent to handle
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

#include <event2/event.h>

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

static void
daytime_udp(evutil_socket_t evfd, short evwhat, void *evarg)
{
    char message[128];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    struct sockaddr_storage from;
    socklen_t fromlen = sizeof(from);
    int n;
    int fd = evfd;

    (void) evwhat;
    (void) evarg;

    n = recvfrom(fd, message, sizeof(message), 0,
                 (struct sockaddr *) &from, &fromlen);
    if (n == -1) {
        syslog(LOG_ERR, "recvfrom failed: %s", strerror(errno));
        return;
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
	    return;
	}
    }
}

/*
 * Implement the daytime protocol, loosely modeled after RFC 867.
 */

static void
daytime_tcp(evutil_socket_t evfd, short evwhat, void *evarg)
{
    size_t n;
    int cfd;
    char message[128];
    int listenfd = evfd;

    (void) evwhat;
    (void) evarg;

    cfd = tcp_accept(listenfd);
    if (cfd == -1) {
        return;
    }

    if (strdaytime(message, sizeof(message)) == 0) {
	goto done;
    }
    
    n = tcp_write(cfd, message, strlen(message));
    if (n != strlen(message)) {
        syslog(LOG_ERR, "write failed");
	goto done;
    }

done:
    tcp_close(cfd);
}

int
main(int argc, char *argv[])
{
    int tfd, ufd;
    struct event_base *evb;
    struct event *tev, *uev;
    const char *interfaces[] = { "0.0.0.0", "::", NULL };
    int i;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s port\n", progname);
        exit(EXIT_FAILURE);
    }

    (void) daemon(0, 0);

    openlog(progname, LOG_PID, LOG_DAEMON);

    evb = event_base_new();
    if (! evb) {
        syslog(LOG_ERR, "creating event base failed");
	return EXIT_FAILURE;
    }

    for (i = 0; interfaces[i]; i++) {
	ufd = udp_open(interfaces[i], argv[1]);
	tfd = tcp_listen(interfaces[i], argv[1]);

	if (tfd > -1) {
	    tev = event_new(evb, tfd, EV_READ|EV_PERSIST, daytime_tcp, NULL);
	    event_add(tev, NULL);
	}
	
	if (ufd > -1) {
	    uev = event_new(evb, ufd, EV_READ|EV_PERSIST, daytime_udp, NULL);
	    event_add(uev, NULL);
	}
    }
	
    if (event_base_loop(evb, 0) == -1) {
        syslog(LOG_ERR, "event loop failed");
        event_base_free(evb);
	return EXIT_FAILURE;
    }
    
    closelog();

    event_base_free(evb);

    return EXIT_SUCCESS;
}
