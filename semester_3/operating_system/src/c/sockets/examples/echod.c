/*
 * socket/examples/echod.c --
 *
 *      A very basic TCP echo daemon supporting sequential, forking,
 *      and threaded execution modes. This version also supports an
 *      event-driven execution mode (not yet event-driven writing).
 */

#define _POSIX_C_SOURCE 201112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <pthread.h>

#include "tcp.h"

typedef struct {
    char *address;
    int fd;
} listen_t;

static void usage(FILE *stream, int status)
{
    (void) fprintf(stream, "Usage: echod [-f] [-s] [-t] port\n");
    exit(status);
}

static void echo_loop(int cfd)
{
    int rc;

    do {
        rc = tcp_read_write(cfd, cfd);
    } while (rc > 0);
    (void) close(cfd);
}

static void echo_event(int cfd)
{
    (void) cfd;
}

static void echo_fork(int cfd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {
        echo_loop(cfd);
        exit(EXIT_SUCCESS);
    }
    (void) close(cfd);                  /* Not needed by the parent. */
}

static void* echo_thread_go(void *arg)
{
    int cfd = (intptr_t) arg;

    echo_loop(cfd);
    return NULL;
}

static void echo_thread(int cfd)
{
    int rc;
    pthread_t tid;
    
    rc = pthread_create(&tid, NULL, echo_thread_go, (void *) (intptr_t) cfd);
    if (rc != 0) {
        (void) fprintf(stderr, "pthread_create failed\n");
    }
}

static void mainloop(listen_t *listeners, void (*echo)(int))
{
#define CFDS_SIZE 1024
    int cfds[CFDS_SIZE];        /* client file descriptors (event-driven) */
    int no_clients = 0;         /* number of entries of cfds in use */
    
    /*
     * The main event loop starts here. We continue until there is no
     * file descriptor left we are waiting on.
     */

    while (1) {
        fd_set fdset;
        FD_ZERO(&fdset);
        int maxfd = 0;
        for (listen_t *l = listeners; l->address; l++) {
            if (l->fd > 0) {
                FD_SET(l->fd, &fdset);
                maxfd = (l->fd > maxfd) ? l->fd : maxfd;
            }
        }
        if (echo == echo_event) {
            for (int i = 0; i < no_clients; i++) {
                FD_SET(cfds[i], &fdset);
                maxfd = (cfds[i] > maxfd) ? cfds[i] : maxfd;
            }
        }
        if (maxfd == 0) {
            break;
        }
        if (select(1 + maxfd, &fdset, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
	}
        for (listen_t *l = listeners; l->address; l++) {
            if (l->fd > 0 && FD_ISSET(l->fd, &fdset)) {                
                /*
                 * Note that we let the parent process / main thread
                 * accept the new connection.  If we let the child
                 * process / thread do this, then we can run into the
                 * situation that the subsequent select may see the
                 * socket as still readable (in case the process /
                 * thread did not yet run to accept from the socket)
                 * and then the main loop may create yet another child
                 * process / thread.
                 */
                int cfd = tcp_accept(l->fd);
                if (cfd == -1) {
                    perror("accept");
                } else {
                    if (echo == echo_event) {
                        if (no_clients+1 < CFDS_SIZE) {
                            cfds[no_clients++] = cfd;
                        } else {
                            fprintf(stderr, "too many clients\n");
                            close(cfd);
                        }
                    } else {
                        echo(cfd);
                    }
                }
            }
        }
        if (echo == echo_event) {
            for (int i = 0; i < no_clients; i++) {
                if (FD_ISSET(cfds[i], &fdset)) {
                    int rc = tcp_read_write(cfds[i], cfds[i]);
                    if (rc == 0) {
                        close(cfds[i]);
                        memmove(cfds+i, cfds+(i+1),
                                (no_clients-i) * sizeof(int));
                        no_clients--;
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    void (*echo)(int) = echo_loop;
    int opt, ignore[] = { SIGPIPE, SIGCHLD, 0 };
    listen_t *iface, interfaces[] = {
        { .address = "0.0.0.0" },               /* IPv4 any address */
        { .address = "::" },                    /* IPv6 any address */
        { .address = NULL }                     /* end marker */
    };

    while ((opt = getopt(argc, argv, "efst")) != -1) {
        switch (opt) {
        case 'e':
            echo = echo_event;
            break;
        case 'f':
            echo = echo_fork;
            break;
        case 's':
            echo = echo_loop;
            break;
        case 't':
            echo = echo_thread;
            break;
        default: /* '?' */
            usage(stderr, EXIT_FAILURE);
        }
    }
    
    if (optind != argc-1) {
        usage(stderr, EXIT_FAILURE);
    }

    /*
     * Setting the SIGCHLD handler to SIG_IGN causes the kernel to
     * discard exit codes returned by child processes. Hence, they do
     * not become zombies waiting until some parent process picks up
     * the exit code.
     */

    for (int i = 0; ignore[i]; i++) {
        if (signal(ignore[i], SIG_IGN) == SIG_ERR) {
            perror("signal");
            return EXIT_FAILURE;
        }
    }

    /*
     * Create listening sockets for the transport addresses we want to
     * listen on.
     */

    for (iface = interfaces; iface->address; iface++) {
        iface->fd = tcp_listen(iface->address, argv[optind]);
        if (iface->fd == -1) {
            (void) fprintf(stderr, "listening on %s port %s failed\n",
                           iface->address, argv[optind]);
	    continue;
	}
    }

    mainloop(interfaces, echo);
    
    return EXIT_SUCCESS;
}
