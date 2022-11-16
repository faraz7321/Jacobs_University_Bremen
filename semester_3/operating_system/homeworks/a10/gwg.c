#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <pthread.h>
#include <netdb.h>
#include <errno.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <fcntl.h>
#include "player.h"
#include "chlng.h"
#include "lib/tcp.h"

#define CFDS_SIZE 1024

int cfds[CFDS_SIZE];
int no_clients = 0;
extern char *optarg;

typedef struct
{
    char *address;
    int fd;
} listen_t;

static int gwg(int fd);
static void usage(FILE *stream, int status);
static void game_block(int fd);
static void game_fork(int fd);
static void *game_thread_go(void *arg);
static void game_thread(int fd);

int main(int argc, char *argv[])
{
    // signal(SIGINT, sig_handler);
    void (*gameType)(int) = game_block;
    int opt, ignore[] = {SIGPIPE, SIGCHLD, 0};
    listen_t *iface, interfaces[] = {
                         {.address = "0.0.0.0"}, /* IPv4 any address */
                         {.address = "::"},      /* IPv6 any address */
                         {.address = NULL}       /* end marker */
                     };

    while ((opt = getopt(argc, argv, "fst")) != -1)
    {
        switch (opt)
        {
        case 'f':
            gameType = game_fork;
            break;
        case 's':
            gameType = game_block;
            break;
        case 't':
            gameType = game_thread;
            break;
        default: /* '?' */
            usage(stderr, EXIT_FAILURE);
        }
    }

    if (optind != argc - 1)
    {
        usage(stderr, EXIT_FAILURE);
    }

    // ignore signals
    for (int i = 0; ignore[i]; i++)
    {
        if (signal(ignore[i], SIG_IGN) == SIG_ERR)
        {
            perror("signal");
            return EXIT_FAILURE;
        }
    }

    /*
     * Create listening sockets for the interfaces we want to
     * listen on.
     */

    for (iface = interfaces; iface->address; iface++)
    {
        iface->fd = tcp_listen(iface->address, argv[optind]);
        if (iface->fd == -1)
        {
            fprintf(stderr, "listening on %s port %s failed\n",
                    iface->address, argv[optind]);
            continue;
        }
    }

    while (1)
    {
        fd_set fdset;
        FD_ZERO(&fdset);
        int maxfd = 0;
        for (iface = interfaces; iface->address; iface++)
        {
            if (iface->fd > 0)
            {
                FD_SET(iface->fd, &fdset);
                maxfd = (iface->fd > maxfd) ? iface->fd : maxfd;
            }
        }
        if (maxfd == 0)
        {
            break;
        }
        if (select(1 + maxfd, &fdset, NULL, NULL, NULL) == -1)
        {
            perror("select");
            return EXIT_FAILURE;
        }
        for (iface = interfaces; iface->address; iface++)
        {
            if (iface->fd > 0 && FD_ISSET(iface->fd, &fdset))
            {
                gameType(iface->fd);
            }
        }
    }

    return EXIT_SUCCESS;
}

static int gwg(int fd)
{
    int rc;
    player_t *p;
    char *msg;

    p = player_new();
    if (!p)
    {
        puts("Could not allocate player");
        return -1;
    }

    rc = player_get_greeting(p, &msg);

    if (rc > 0)
    {
        tcp_write(fd, msg, rc);
        free(msg);
    }

    while (p->state != FINISHED)
    {
        char *msg = NULL;
        char line[1024];

        if (p->state != CONTINUE)
        {
            player_fetch_chlng(p);
        }

        rc = player_get_challenge(p, &msg);

        if (rc > 0)
        {
            tcp_write(fd, msg, rc);
            free(msg);
        }
        else
        {
            perror("player_get_challenge");
        }

        rc = tcp_read(fd, line, 1024);
        // socket closed
        if (rc <= 0)
        {
            perror("socket closed");
            break;
        }

        rc = player_post_challenge(p, line, &msg);
        if (rc > 0)
        {
            tcp_write(fd, msg, rc);
            free(msg);
        }
        else
        {
            perror("player_post_challenge");
        }
    }

    player_del(p);
    return 0;
}
static void game_block(int fd)
{
    int cfd;

    cfd = tcp_accept(fd);
    if (cfd == -1)
    {
        return;
    }

    gwg(cfd);
    (void)close(fd);
}
static void game_fork(int fd)
{
    int rc, cfd;

    cfd = tcp_accept(fd);
    if (cfd == -1)
    {
        return;
    }

    rc = fork();
    if (rc == -1)
    {
        perror("fork");
        return;
    }
    if (rc == 0)
    {
        (void)close(fd); /* Not needed by the child. */
        gwg(cfd);
        (void)close(cfd);
        exit(EXIT_SUCCESS);
    }
    (void)close(cfd); /* Not needed by the parent. */
}
static void *game_thread_go(void *arg)
{
    int cfd = (long)arg;

    gwg(cfd);
    (void)close(cfd);
    return NULL;
}

static void game_thread(int fd)
{
    int rc, cfd;
    pthread_t tid;

    cfd = tcp_accept(fd);
    if (cfd == -1)
    {
        return;
    }
    rc = pthread_create(&tid, NULL, game_thread_go, (void *)(long)cfd);
    if (rc != 0)
    {
        fprintf(stderr, "pthread_create failed\n");
    }
}
static void usage(FILE *stream, int status)
{
    (void)fprintf(stream, "Usage: echod [-f] [-s] [-t] port\n");
    exit(status);
}