/*
 * pthread/pthread-fork.c --
 *
 *      A simple program to start threads and processes which allows
 *      to compare execution costs of thread and process creation.
 */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

static const char *progname = "pthread";

static int dflag = 0;

static pid_t (*mfork)(void) = NULL;

static void* work(void *data)
{
    (void) data;

    if (dflag) {
        printf("%s: worker pid = %d\n", progname, getpid());
    }
    return NULL;
}

static void run_threads(unsigned int n)
{
    pthread_t *thread;
    int rc;

    thread = (pthread_t *) calloc(n, sizeof(pthread_t));
    if (! thread) {
        fprintf(stderr, "%s: %s: %s\n", progname, __func__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < n; i++) {
        rc = pthread_create(&thread[i], NULL, work, NULL);
        if (rc) {
            fprintf(stderr, "%s: %s: unable to create thread %d: %s\n",
                    progname, __func__, i, strerror(rc));
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        if (thread[i]) {
            (void) pthread_join(thread[i], NULL);
        }
    }

    (void) free(thread);
}

static void run_processes(unsigned int n)
{
    pid_t *pid;

    pid = (pid_t *) calloc(n, sizeof(pid_t));
    if (! pid) {
        fprintf(stderr, "%s: %s: %s\n", progname, __func__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < n; i++) {
        pid[i] = mfork();
        if (pid[i] == -1) {
            fprintf(stderr, "%s: %s: unable to create process %d: %s\n",
                    progname, __func__, i, strerror(errno));
        }
        if (pid[i] == 0) {
            (void) work(NULL);
            _exit(EXIT_SUCCESS);
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        if (pid[i] > 0) {
            (void) waitpid(pid[i], NULL, 0);
        }
    }    

    (void) free(pid);
}

static double timeit(void (*proc)(unsigned int n), int n, int r)
{
    clock_t t1, t2;
    t1 = clock();
    for (int i = 0; i < r; i++) {
        proc(n);
    }
    t2 = clock();
    return ((double) t2 - (double) t1) / CLOCKS_PER_SEC * 1000 / n / r;
}

static unsigned int parse(const char *s)
{
    int x;
    char *end;

    x = strtol(s, &end, 10);
    if (*end || x <= 0) {
        fprintf(stderr, "%s: illegal number: %s\n", progname, s);
        exit(EXIT_FAILURE);
    }
    return x;
}

int main(int argc, char *argv[])
{
    const char *usage
        = "Usage: %s [-n forks/threads] [-r repetitions] [-t] [-p] [-a] [-d] [-v] [-h]\n";
    unsigned int n = 100, r = 1, tflag = 0, pflag = 0, vflag = 0;
    int c;
    double ms;

    while ((c = getopt(argc, argv, "n:r:tpadvh")) >= 0) {
        switch (c) {
        case 'n':
            n = parse(optarg);
            break;
        case 'r':
            r = parse(optarg);
            break;
        case 't':
            tflag = 1;
            break;
        case 'p':
            pflag = 1;
            break;
        case 'a':
            tflag = 1;
            pflag = 1;
            vflag = 1;
            break;
        case 'h':
            printf(usage, progname);
            exit(EXIT_SUCCESS);
        case 'd':
            dflag = 1;
            break;
        case 'v':
            vflag = 1;
            break;
        case ':':
        case '?':
            exit(EXIT_FAILURE);
        }
    }

    if (argc != optind) {
        fprintf(stderr, usage, progname);
        exit(EXIT_FAILURE);
    }

    if (pflag) {
        mfork = fork;
        ms = timeit(run_processes, n, r);
        (void) printf("%d x %d processes: %8.3f ms (fork)\n", r, n, ms);
    }

    if (tflag) {
        ms = timeit(run_threads, n, r);
        (void) printf("%d x %d threads:   %8.3f ms\n", r, n, ms);
    }

    if (vflag) {
        mfork = vfork;
        ms = timeit(run_processes, n, r);
        (void) printf("%d x %d processes: %8.3f ms (vfork)\n", r, n, ms);
    }

    return EXIT_SUCCESS;
}
