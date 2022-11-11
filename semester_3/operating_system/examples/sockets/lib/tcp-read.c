/*
 * socket/lib/tcp-read.c --
 *
 *	The tcp_read() function behaves like read(), but it handles
 *	interrupted system calls, short reads, and non-blocking file
 *	descriptors.
 */

#define _POSIX_C_SOURCE 201112L

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "tcp.h"

ssize_t tcp_read(int fd, void *buf, size_t count)
{
    size_t nread = 0;
    int flags;
    
    flags = fcntl(fd, F_GETFD);
    if (flags == -1) {
        return -1;
    }
    
    while (count > 0) {
	int r = read(fd, buf, count);
	if (r < 0 && errno == EINTR) {
	    continue;
	}
	if (r < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
	    return nread;
	}
	if (r < 0) {
	    return r;
	}
	if (r == 0) {
	    return nread;
	}
	buf = (unsigned char *) buf + r;
	count -= r;
	nread += r;
        if ((flags & O_NONBLOCK) == 0) {
            return nread;
        }
    }
    
    return nread;
}
