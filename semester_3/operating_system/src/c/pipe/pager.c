/*
 * pipe/pager.c --
 *
 *	This program demonstrates the usage of pipes. It displays
 *	texts read from stdin either by writing it directly to stdout
 *	if it contains only a few lines or by piping the text through
 *	a pager.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static const char *progname = "pipe";

static const char *less = "/usr/bin/less";

static int page(char *text)
{
    ssize_t len, cnt;
    int status;
    pid_t pid;
    int fd[2];

    status = pipe(fd);
    if (status == -1) {
        perror(progname);
        return EXIT_FAILURE;
    }
    
    pid = fork();
    if (pid == -1) {
        perror(progname);
        return EXIT_FAILURE;
    }
    if (pid == 0) {
        close(fd[1]);
        status = dup2(fd[0], STDIN_FILENO);
        if (status == -1) {
            perror(progname);
            return EXIT_FAILURE;
        }
        close(fd[0]);
        execl(less, less, NULL);
        perror(progname);
        _exit(EXIT_FAILURE);
    } else {
        close(fd[0]);
        status = dup2(fd[1], STDOUT_FILENO);
        if (status == -1) {
            perror(progname);
            return EXIT_FAILURE;
        }
        close(fd[1]);
        for (len = strlen(text); len; len -= cnt, text += cnt) {
            cnt = write(STDOUT_FILENO, text, len);
            if (cnt == -1) {
                perror(progname);
                return EXIT_FAILURE;
            }
        }
        close(STDOUT_FILENO);
	do {
	    if (waitpid(pid, &status, 0) == -1) {
		perror(progname);
		return EXIT_FAILURE;
	    }
	    if (WIFEXITED(status)) {
		if (WEXITSTATUS(status)) {
		    fprintf(stderr, "%s: process exited with status %d\n",
			    progname, WEXITSTATUS(status));
		}
	    } else if (WIFSIGNALED(status)) {
		fprintf(stderr, "%s: process exited with signal %d\n",
			progname, WTERMSIG(status));
	    }
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return EXIT_SUCCESS;
}

static int show_text(char *text)
{
    unsigned long newlines = 0;
    char *p;

    for (p = text; *p; p++) {
        if (*p == '\n') newlines++;
    }

    if (newlines < 24) {
        fputs(text, stdout);
        return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    return page(text);
}

static char* read_text()
{
    char *text = NULL;
    size_t i = 0, len = 32;
    int c;

    text = malloc(len + 1);
    if (! text) {
	fprintf(stderr, "%s: out of memory\n", progname);
	exit(EXIT_FAILURE);
    }
    
    while ((c = getchar()) != EOF) {
        if (i == len) {
            len *= 2;
            text = realloc(text, len + 1);
            if (! text) {
                fprintf(stderr, "%s: out of memory\n", progname);
                exit(EXIT_FAILURE);
            }
        }
	text[i++] = c;
    }
    text[i] = 0;

    return text;
}

int main(void)
{
    char *text;
    int code = EXIT_SUCCESS;
    
    text = read_text();
    if (text) {
        code = show_text(text);
        free(text);
    }
    
    return code;
}
