/*
 * wc/wc.c --
 *
 *      A simple program to count words in files concurrently. For
 *      each file, a separate thread is created to count the words.
 */

#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

static const char *progname = "wc";

static int tflag = 0;

typedef struct task {
    const char   *filename;
    unsigned int chars;
    unsigned int words;
    unsigned int lines;
    pthread_t    thread;
} task_t;

static void*
wc(void *data)
{
    task_t *task = (task_t *) data;
    FILE *f;
    int c, l = ' ';

    assert(task && task->filename);

    f = fopen(task->filename, "r");
    if (! f) {
        fprintf(stderr, "%s: %s: %s\n",
                progname, task->filename, strerror(errno));
        return NULL;
    }

    while (EOF != (c = fgetc(f))) {
        task->chars++;
        if (c == '\n') task->lines++;
        if (!isspace(c) && isspace(l)) {
            task->words++;
        }
        l = c;
    }
    
    if (ferror(f)) {
        task = NULL;
    }
    (void) fclose(f);
    return task;
}

static int
run_threads(int argc, char *argv[])
{
    task_t tasks[argc];
    unsigned int chars = 0, words = 0, lines = 0;
    int err, rcode = EXIT_SUCCESS;
    void *result;

    assert(argc >= 0);

    memset(tasks, 0, sizeof(tasks));

    for (int i = 0; i < argc; i++) {
        tasks[i].filename = argv[i];
        err = pthread_create(&tasks[i].thread, NULL, wc, &tasks[i]);
        if (err != 0) {
            fprintf(stderr, "%s: unable to create thread %d: %d\n",
                    progname, i, err);
            rcode = EXIT_FAILURE;
        }
    }

    for (int i = 0; i < argc; i++) {
        if (tasks[i].thread) {
            err = pthread_join(tasks[i].thread, &result);
            if (err) {
                fprintf(stderr, "%s: unable to join thread %d: %d\n",
                        progname, i, err);
                rcode = EXIT_FAILURE;
            }
            if (result) {
                printf("%5u %5u %5u %s\n", 
                       tasks[i].lines, tasks[i].words, tasks[i].chars,
                       tasks[i].filename);
                chars += tasks[i].chars;
                words += tasks[i].words;
                lines += tasks[i].lines;
            } else {
                rcode = EXIT_FAILURE;
            }
        }
    }
    if (argc > 1) {
        printf("%5u %5u %5u total\n", lines, words, chars);
    }

    if (fflush(stdout) == EOF) {
        rcode = EXIT_FAILURE;
    }

    return rcode;
}


static int
run_sequentially(int argc, char *argv[])
{
    task_t task;
    unsigned int chars = 0, words = 0, lines = 0;
    int rcode = EXIT_SUCCESS;
    void *result;

    assert(argc >= 0);

    for (int i = 0; i < argc; i++) {
        memset(&task, 0, sizeof(task));
        task.filename = argv[i];
        result = wc(&task);
        if (result) {
            printf("%5u %5u %5u %s\n", 
                   task.lines, task.words, task.chars,
                   task.filename);
            chars += task.chars;
            words += task.words;
            lines += task.lines;
        } else {
            rcode = EXIT_FAILURE;
        }
    }
    if (argc > 1) {
        printf("%5u %5u %5u total\n", lines, words, chars);
    }

    if (fflush(stdout) == EOF) {
        rcode = EXIT_FAILURE;
    }

    return rcode;
}


int
main(int argc, char *argv[])
{
    const char *usage = "Usage: %s [-t] file ...\n";
    int c, code;

    while ((c = getopt(argc, argv, "ht")) >= 0) {
        switch (c) {
        case 'h':
            printf(usage, progname);
            exit(EXIT_SUCCESS);
        case 't':
            tflag = 1;
            break;
        case ':':
        case '?':
            exit(EXIT_FAILURE);
        }
    }
    argc -= optind;
    argv += optind;

    code = tflag ? run_threads(argc, argv) : run_sequentially(argc, argv);
    return code;
}
