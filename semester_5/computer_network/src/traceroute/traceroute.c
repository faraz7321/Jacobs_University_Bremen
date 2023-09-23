/*
 * traceroute/traceroute.c --
 */

#define _POSIX_C_SOURCE 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>

#include <linux/errqueue.h>

static const char *progname = "traceroute";

#ifndef NI_MAXHOST
#define NI_MAXHOST      1025
#endif

static int hop_limit = 64;
static int timeout_secs = 5;
static char *port = "33434";

/*
 * A wrapper around getnameinfo to turn an address into a
 * numeric host name.
 */

static char *
name(struct sockaddr *addr, socklen_t addrlen)
{
    static char host[NI_MAXHOST];
    int n;

    host[0] = 0;
    n = getnameinfo(addr, addrlen,
		    host, sizeof(host), NULL, 0,
		    NI_NUMERICHOST);
    if (n) {
	fprintf(stderr, "%s: %s", progname, gai_strerror(n));
	host[0] = '?';
	host[1] = 0;
    }

    return host;
}

/*
 * Do a single probe for a given ttl.
 */

static void
probe(int sd, int ttl, const struct sockaddr *addr, socklen_t addrlen)
{
    int n;
    ssize_t s;
    char buf[] = "hello world";
    fd_set fdset;
    struct timeval timeout;

    n = setsockopt(sd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
    if (n == -1) {
	fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	return;
    }

    s = sendto(sd, buf, sizeof(buf), 0, addr, addrlen);
    if (s == -1) {
	fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	return;
    }

#if 1
    timeout.tv_sec = timeout_secs;
    timeout.tv_usec = 0;
    FD_ZERO(&fdset);
    FD_SET(sd, &fdset);
    if (select(1 + sd, &fdset, NULL, NULL, &timeout) == -1) {
	fprintf(stderr, "%s: select failed: %s\n",
		progname, strerror(errno));
	return;
    }
    
    if (! FD_ISSET(sd, &fdset)) {
	printf("%3d: *\n", ttl);
	return;
    }
#endif

#if 1
    {
	char buffer[2048];
	char control[1024];
	
	struct iovec io;
	struct msghdr msg;
	struct cmsghdr *cmsg;

	io.iov_base = buffer;
	io.iov_len = sizeof(buffer);

	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = control;
	msg.msg_controllen = sizeof(control);
	
	n = recvmsg(sd, &msg, MSG_ERRQUEUE);
	if (n == -1) {
	    fprintf(stderr, "%s: recvmsg failed: %s\n",
		    progname, strerror(errno));
	    return;
	}
	if (!n) {
	    printf("%3d: {oops?}\n", ttl);
	}
	if (n) {
	    for (cmsg = CMSG_FIRSTHDR(&msg);
		 cmsg != NULL;
		 cmsg = CMSG_NXTHDR(&msg, cmsg)) {
		if (cmsg->cmsg_level == IPPROTO_IP
		    && cmsg->cmsg_type == IP_RECVERR) {
		    struct sock_extended_err *err;
		    err = (struct sock_extended_err *) CMSG_DATA(cmsg);
#if 0
		    if (err->ee_origin == SO_EE_ORIGIN_ICMP) {
			fprintf(stderr, "** ICMPv4 type %d, code %d\n",
				err->ee_type, err->ee_code);
		    }
		    if (err->ee_origin == SO_EE_ORIGIN_ICMP6) {
			fprintf(stderr, "** ICMPv6 type %d, code %d\n",
				err->ee_type, err->ee_code);
		    }
#endif
#define ICMP_TYPE_DESTINATION_UNREACHABLE 3
#define ICMP_CODE_PORT_UNREACHABLE 3
#define ICMP_TYPE_TIME_EXCEEDED 11
#define ICMP_CODE_TTL_EXCEEDED_IN_TRANSIT 0
		    switch (err->ee_type) {
		    case ICMP_TYPE_DESTINATION_UNREACHABLE:
			switch (err->ee_code) {
			case ICMP_CODE_PORT_UNREACHABLE:
			    printf("%3d: port unreachable\n", ttl);
			    break;
			}
			break;
		    case ICMP_TYPE_TIME_EXCEEDED:
			switch (err->ee_code) {
			case ICMP_CODE_TTL_EXCEEDED_IN_TRANSIT:
			    printf("%3d: ttl exceeded in transit\n", ttl);
			    break;
			}
			break;
		    }
		}
	    }
	}
    }
#endif
}

/*
 * Resolve the given host name to an IP address and probe over
 * increasing ttls.
 */

static void
traceroute(const char *host)
{
    struct addrinfo hints, *ai_list, *ai;
    int n, sd, ttl, on = 1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    n = getaddrinfo(host, port, &hints, &ai_list);
    if (n) {
	fprintf(stderr, "%s: %s: %s\n",
		progname, host, gai_strerror(n));
	return;
    }

    for (n = 0, ai = ai_list; ai; ai = ai->ai_next, n++) ;

    for (ai = ai_list; ai; ai = ai->ai_next) {
	sd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if (sd < 0) {
	    switch (errno) {
	    case EAFNOSUPPORT:
	    case EPROTONOSUPPORT:
		continue;

	    default:
		fprintf(stderr, "%s: socket: %s\n",
			progname, strerror(errno));
		continue;
	    }
	}
	break;  /* still here? we were successful and we are done */
    }

    freeaddrinfo(ai_list);

    if (ai == NULL) {
	fprintf(stderr, "%s: could not create socket for %s port %s\n",
		progname, host, port);
	exit(EXIT_FAILURE);
    }

    if (n) {
	printf("Warning: %s has multiple addresses; using %s, %d hops max\n",
	       host, name(ai->ai_addr, ai->ai_addrlen), hop_limit);
    }

#if 1
    n = setsockopt(sd, IPPROTO_IP, IP_RECVERR, &on, sizeof(on));
    if (n == -1) {
	fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	return;
    }
#endif

    for (ttl = 1; ttl <= hop_limit; ttl++) {
	probe(sd, ttl, ai->ai_addr, ai->ai_addrlen);
    }

    (void) close(sd);
}

/*
 * Option processing, main loop over all host names provided.
 */

int main(int argc, char *argv[])
{
    int i, c;

    while ((c = getopt(argc, argv, "m:w:")) != -1) {
	switch (c) {
	case 'm':
	    hop_limit = atoi(optarg);
	    break;
	case 'w':
	    timeout_secs = atoi(optarg);
	    break;
	default:
	    fprintf(stderr, "usage: %s [-m ttl] [-w timeout] name\n", progname);
	    exit(EXIT_FAILURE);
	}
    }

    for (i = optind; i < argc; i++) {
	traceroute(argv[i]);
    }
    
    return EXIT_SUCCESS;
}
