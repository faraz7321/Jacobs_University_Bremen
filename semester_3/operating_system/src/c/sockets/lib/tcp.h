/*
 * socket/lib/tcp.h --
 *
 */

#ifndef _TCP_H
#define _TCP_H

#include <sys/types.h>

extern int tcp_connect(const char *host, const char *port);
extern int tcp_listen(const char *host, const char *port);
extern int tcp_accept(int listen);
extern ssize_t tcp_read(int fd, void *buf, size_t count);
extern ssize_t tcp_write(int fd, const void *buf, size_t count);
extern int tcp_read_write(int sfd, int dfd);
extern int tcp_chat(int fd);
extern int tcp_close(int fd);

#endif
