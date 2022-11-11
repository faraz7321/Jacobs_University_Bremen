/*
 * socket/lib/udp.h --
 *
 */

#ifndef _UDP_H
#define _UDP_H

extern int udp_socket(const char *host, const char *port);
extern int udp_connect(const char *host, const char *port);
extern int udp_read_send(int sfd, int dfd);
extern int udp_recv_write(int sfd, int dfd);
extern int udp_chat(int fd);
extern int udp_close(int fd);

#endif
