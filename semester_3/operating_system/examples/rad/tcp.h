/*
 * rad/tcp.h --
 *
 * See Operating Systems 2015 homework sheet #5.
 */

#ifndef _TCP_H
#define _TCP_H

extern int tcp_connect(char *host, char *port);
extern int tcp_listen(char *port);
extern int tcp_accept(int listen);
extern int tcp_close(int fd);

#endif
