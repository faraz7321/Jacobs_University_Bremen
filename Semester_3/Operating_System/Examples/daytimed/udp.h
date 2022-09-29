/*
 * daytimed/udp.h --
 *
 * A couple of wrapper functions for simple UDP server applications.
 */

#ifndef _UDP_H
#define _UDP_H

#include <unistd.h>

extern int udp_open(const char *host, const char *port);

extern int udp_close(int fd);

#endif
