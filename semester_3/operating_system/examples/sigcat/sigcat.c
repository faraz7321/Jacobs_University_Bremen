/*
 * sigcat/sigcat.c --
 *
 *	This is a special version of cat that restarts upon receiving
 *	a SIGHUP if called with the -f option and which will restart
 *	every n seconds if called with the -t n option. Both options
 *	can be combined.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

static const char progname[] = "sigcat";

static volatile sig_atomic_t sighup_pending = 0;
static volatile sig_atomic_t sigalrm_pending = 0;

static void
catch(int signum)
{
    switch (signum) {
    case SIGHUP:
        sighup_pending = 1;
        break;
    case SIGALRM:
        sigalrm_pending = 1;
        break;
    default:
        break;
    }
}

static int
cat(const char *filename)
{
    FILE *in;
    int c;

    if (! filename || strcmp(filename, "-") == 0) {
        clearerr(stdin);
        in = stdin;
    } else {
        in = fopen(filename, "r");
        if (! in) {
            perror(progname);
            return -1;
        }
    }

    while ((c = getc(in)) != EOF) {
        putc(c, stdout);
    }

    if (fflush(stdout) || ferror(stdout) || ferror(in)) {
        perror(progname);
        exit(1);
    }

    if (in != stdin) {
        fclose(in);
    }

    return 0;
}

int
main(int argc, char *argv[])
{
    int i, c, status = EXIT_SUCCESS, seconds, fflag = 0, tflag = 0;
    struct sigaction sa;
    sigset_t mask, old_mask;
    
    while ((c = getopt(argc, argv, "ft:h")) >= 0) {
        switch (c) {
        case 'f':
            fflag = 1;
            break;
        case 't':
            tflag = 1;
            if ((seconds = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of seconds must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            printf("Usage: %s [-f] [-h]\n", progname);
            exit(EXIT_SUCCESS);
        }
    }

    if (fflag || tflag) {
        sa.sa_handler = catch;
        sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
        if (fflag) {
            if (sigaction(SIGHUP, &sa, NULL) != 0) {
                perror(progname);
                return EXIT_FAILURE;
            }
        }
        if (tflag) {
            if (sigaction(SIGALRM, &sa, NULL) != 0) {
                perror(progname);
                return EXIT_FAILURE;
            }
        }
    }

    if (fflag || tflag) {
        (void) sigemptyset(&mask);
        if (fflag) (void) sigaddset(&mask, SIGHUP);
        if (tflag) (void) sigaddset(&mask, SIGALRM);
        if (sigprocmask(SIG_BLOCK, &mask, &old_mask) == -1) {
	    perror(progname);
	    return EXIT_FAILURE;
	}
    }
        
    do {
        if (optind == argc) {
            if (cat(NULL) < 0) {
                status = EXIT_FAILURE;
            }
        } else {
            for (i = optind; i < argc; i++) {
                if (cat(argv[i]) < 0) {
                    status = EXIT_FAILURE;
                }
            }
        }
        sighup_pending = sigalrm_pending = 0;
        if (tflag) {
            (void) alarm(seconds);
        }
        if (fflag || tflag) {
            (void) sigsuspend(&old_mask);
        }
    } while ((fflag && sighup_pending) || (tflag && sigalrm_pending));

    return status;
}
