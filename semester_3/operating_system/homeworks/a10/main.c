#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <fcntl.h>
#include "player.h"
#include "chlng.h"
#include "lib/tcp.h"

int main(int argc, char *argv[])
{
    char opt;
    char *port = "8080";
    char *host4 = "0.0.0.0";
    char *host6 = "::";

    while ((opt = getopt(argc, argv, "p:")) != -1)
    {
        if (opt == 'p')
        {
            port = optarg;
        }
    }

    int server_socket4_fd = tcp_listen(host4, port);
    int server_socket6_fd = tcp_listen(host6, port);

    int bigger_fd = server_socket6_fd > server_socket4_fd ? server_socket6_fd + 1 : server_socket4_fd + 1;
    int client_socket_fd;

    while (1)
    {
        fd_set rfds;

        FD_ZERO(&rfds);
        FD_SET(server_socket4_fd, &rfds);
        FD_SET(server_socket6_fd, &rfds);

        int rc = select(bigger_fd, &rfds, NULL, NULL, NULL);

        if (rc == -1)
        {
            perror("Select: ");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(server_socket4_fd, &rfds))
        {
            client_socket_fd = accept(server_socket4_fd, NULL, NULL);
        }
        else if (FD_ISSET(server_socket6_fd, &rfds))
        {
            client_socket_fd = accept(server_socket6_fd, NULL, NULL);
        }

        if (client_socket_fd == -1)
        {
            perror("Client socket creation, accept: ");
            continue;
        }

        choose_mode(client_socket_fd, quiz_mode);
    }
}