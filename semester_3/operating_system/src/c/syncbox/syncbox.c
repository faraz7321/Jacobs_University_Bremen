/*
 * syncbox/syncbox.c --
 *
 *	Using the Linux inotify API, detect changes in a src directory
 *	and once changes have been detected, synchronize the src
 *	directory to a dst directory using rsync. For more details,
 *	see the assignment #6 of the OS 2014 course.
 */

#define _POSIX_C_SOURCE 2
#define _DEFAULT_SOURCE

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/inotify.h>

static const char *progname = "syncbox";

#define EVENT_SIZE		( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN		( 1024 * ( EVENT_SIZE + 16 ) )

static volatile sig_atomic_t quit = 0;

static int dry = 0;
static int verbose = 0;

static int dirty = 1;
static pid_t pid = 0;

static void
handle_signal(int signum)
{
    switch (signum) {
    case SIGINT:
	quit = 1;
	break;
    }
}

static void
synchronize(char *src, char *dst)
{
    if (verbose) {
	printf("%s: synchronizing %s to %s\n", progname, src, dst);
    }

    if (pid) {
	if (verbose) {
	    printf("%s: skipping synchronizing (rsync already running)\n",
		   progname);
	}
	return;
    }

    pid = fork();
    if (pid == -1) {
	fprintf(stderr, "%s: fork failed: %s\n",
		progname, strerror(errno));
	return;
    }
    if (pid == 0) {
	if (verbose || dry) {
	    printf("%s: rsync -az --delete %s %s\n", progname, src, dst);
	}
	if (dry) {
	    _exit(EXIT_SUCCESS);
	}
	execlp("rsync", "rsync", "-az", "--delete", src, dst, NULL);
	fprintf(stderr, "%s: execl failed: %s\n", progname, strerror(errno));
	_exit(EXIT_FAILURE);
    }
}

static void
handle_inotify_event(int fd)
{
    int length, i = 0;
    char buffer[EVENT_BUF_LEN];
    
    length = read(fd, buffer, EVENT_BUF_LEN);
    if (length < 0) {
	fprintf(stderr, "%s: read failed: %s\n",
		progname, strerror(errno));
	return;
    }
    
    while (i < length) {
	struct inotify_event *event;
	
	event = (struct inotify_event *) &buffer[i];
	if (event->mask & IN_DELETE_SELF) {
	    if (verbose) {
		printf("%s: watched file or directory deleted - exiting\n",
		       progname);
	    }
	    quit = 1;
	}
	if (event->len) {
	    if (event->mask & IN_CREATE) {
		if (verbose) {
		    printf("%s: %s %s created\n",
			   progname,
			   (event->mask & IN_ISDIR) ? "directory" : "file",
			   event->name);
		}
		dirty = 1;
	    }
	    else if (event->mask & IN_DELETE) {
		if (verbose) {
		    printf("%s: %s %s deleted\n",
			   progname,
			   (event->mask & IN_ISDIR) ? "directory" : "file",
			   event->name);
		}
		dirty = 1;
	    }
	    if (event->mask & IN_CLOSE_WRITE) {
		if (verbose) {
		    printf("%s: %s %s closed for writing\n",
			   progname,
			   (event->mask & IN_ISDIR) ? "directory" : "file",
			   event->name);
		}
		dirty = 1;
	    }
	    if (event->mask & IN_MOVED_FROM) {
		if (verbose) {
		    printf("%s: %s %s moved away\n",
			   progname,
			   (event->mask & IN_ISDIR) ? "directory" : "file",
			   event->name);
		}
		dirty = 1;
	    }
	    if (event->mask & IN_MOVED_TO) {
		if (verbose) {
		    printf("%s: %s %s moved into\n",
			   progname,
			   (event->mask & IN_ISDIR) ? "directory" : "file",
			   event->name);
		}
		dirty = 1;
	    }
	}
	i += EVENT_SIZE + event->len;
    }
}
    
int
main(int argc, char *argv[])
{
    char *src, *dst;
    int fd, wd, c;
    unsigned int timeout;
    fd_set fdset;
    struct sigaction sa;
    struct timeval tv, last = { 0, 0 }, now, delta;

    while ((c = getopt(argc, argv, "t:nvh")) >= 0) {
	switch (c) {
	case 'n':
	    dry = 1;
	    break;
	case 't':
	    timeout = atoi(optarg);
	    break;
	case 'v':
	    verbose = 1;
	    break;
	case 'h':
	    printf("Usage: %s [-t seconds] [-v] [-n] src dst\n", progname);
	    exit(EXIT_SUCCESS);
	}
    }

    if (optind < argc-2) {
	fprintf(stderr, "%s: too many arguments\n", progname);
	return EXIT_FAILURE;
    }
    if (optind > argc-2) {
	fprintf(stderr, "%s: missing arguments\n", progname);
	return EXIT_FAILURE;
    }
    src = argv[optind++];
    dst = argv[optind];

    fd = inotify_init();
    if (fd == -1) {
	fprintf(stderr, "%s: inotify_init failed: %s\n",
		progname, strerror(errno));
	return EXIT_FAILURE;
    }

    wd = inotify_add_watch(fd, src,
			   ( IN_DELETE_SELF
			     | IN_CREATE | IN_DELETE | IN_CLOSE_WRITE
			     | IN_MOVED_FROM | IN_MOVED_TO));
    if (wd == -1) {
	fprintf(stderr, "%s: inotify_add_watch failed: %s\n",
		progname, strerror(errno));
	return EXIT_FAILURE;
    }

    if (verbose) {
	printf("%s: added watch for %s\n", progname, src);
    }

    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    while (fd != -1 && ! quit) {
	FD_ZERO(&fdset);
	FD_SET(fd, &fdset);

	if (pid > 0) {
	    int status;
	    if (waitpid(pid, &status, WNOHANG) != -1) {
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
		    if (verbose) {
			printf("%s: synchronization finished\n", progname);
		    }
		    dirty = 0;
		    pid = 0;
		}
	    }
	}

	(void) gettimeofday(&now, NULL);
	timersub(&now, &last, &delta);

	if (delta.tv_sec > timeout) {
	    if (dirty) {
		synchronize(src, dst);
	    }
	    last = now;
	}

	tv.tv_sec = timeout;
	tv.tv_usec = 0;

	if (select(1 + fd, &fdset, NULL, NULL, &tv) == -1) {
	    if (errno == EINTR) {
		continue;
	    }
	    fprintf(stderr, "%s: select failed: %s\n",
		    progname, strerror(errno));
	    break;
	}

	if (FD_ISSET(fd, &fdset)) {
	    handle_inotify_event(fd);
	}
    }

    (void) inotify_rm_watch(fd, wd);
    if (verbose) {
	printf("%s: removed watch for %s\n", progname, src);
    }

    (void) close(fd);    

    return EXIT_SUCCESS;
}
