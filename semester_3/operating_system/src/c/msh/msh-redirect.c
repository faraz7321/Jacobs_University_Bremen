/*
 * msh/msh.c --
 *
 *      This file contains the simple and stupid shell (msh).
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

#include "msh.h"

#define REDIRECT

#ifdef REDIRECT
#include <fcntl.h>
#endif

#ifdef REDIRECT
static int
redirect(int *argc, char **argv, 
         int *redir_stdin_fd, int *redir_stdout_fd, int *redir_stderr_fd)
{
    int i, j, fd;
  
    for (i = 0, j = 0; i < *argc; i++) {
        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], "1>") == 0
            || strcmp(argv[i], "&>") == 0) {
            if (++i == *argc) {
                goto missing_target;
            }
            fd = open(argv[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                goto open_failed;
            }
            if (*redir_stdout_fd) {
                (void) close(*redir_stdout_fd);
            }
            *redir_stdout_fd = fd;
        } else if (strcmp(argv[i], "2>") == 0 || strcmp(argv[i], "&>") == 0) {
            if (++i == *argc) {
                goto missing_target;
            }
            fd = open(argv[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                goto open_failed;
            }
            *redir_stdout_fd = fd;
            if (*redir_stderr_fd) {
                (void) close(*redir_stderr_fd);
            }
            *redir_stderr_fd = fd;
        } else if (strcmp(argv[i], "<") == 0 || strcmp(argv[i], "0<") == 0) {
            if (++i == *argc) {
                goto missing_target;
            }
            fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                goto open_failed;
            }
            if (*redir_stdin_fd) {
                (void) close(*redir_stdin_fd);
            }
            *redir_stdin_fd = fd;
        } else {
            argv[j++] = argv[i];
        }
    }

    *argc = j;
    argv[*argc] = NULL;
    return 0;

 open_failed:
    fprintf(stderr, "%s: opening '%s' failed: %s\n", progname, argv[i],
            strerror(errno));
    goto cleanup;

 missing_target:
    fprintf(stderr, "%s: missing redirect target\n", progname);
    goto cleanup;

 cleanup:
    if (*redir_stdin_fd) {
        (void) close(*redir_stdin_fd);
    }
    if (*redir_stdout_fd) {
        (void) close(*redir_stdout_fd);
    }
    if (*redir_stderr_fd) {
        (void) close(*redir_stderr_fd);
    }
    return -1;
}
#endif

int
main(void)
{
    pid_t pid;
    int status;
    int argc;
    char **argv;
#ifdef REDIRECT
    int redir_stdin_fd, redir_stdout_fd, redir_stderr_fd;
    int code;
#endif

    while (1) {
#ifdef REDIRECT
        redir_stdin_fd = 0, redir_stdout_fd = 0, redir_stderr_fd = 0;
#endif
        msh_show_prompt();
        msh_read_command(stdin, &argc, &argv);
        if (argv[0] == NULL || strcmp(argv[0], "exit") == 0) {
            break;
        }
        if (strlen(argv[0]) == 0) {
            continue;
        }
#ifdef REDIRECT
        code = redirect(&argc, argv,
                        &redir_stdin_fd, &redir_stdout_fd, &redir_stderr_fd);
        if (code == -1) {
            continue;
        }
#endif
        pid = fork();
        if (pid == -1) {
            fprintf(stderr, "%s: fork: %s\n", progname, strerror(errno));
            continue;
        }
        if (pid == 0) {                 /* child */
#ifdef REDIRECT
            if (redir_stdin_fd) {
                if (-1 == dup2(redir_stdin_fd, STDIN_FILENO)) {
                    fprintf(stderr, "%s: redirecting stdin: %s\n", 
                            progname, strerror(errno));
                }
            }
            if (redir_stdout_fd) {
                if (-1 == dup2(redir_stdout_fd, STDOUT_FILENO)) {
                    fprintf(stderr, "%s: redirecting stdout: %s\n", 
                            progname, strerror(errno));
                }
            }
            if (redir_stderr_fd) {
                if (-1 == dup2(redir_stderr_fd, STDERR_FILENO)) {
                    fprintf(stderr, "%s: redirecting stderr: %s\n", 
                            progname, strerror(errno));
                }
            }
#endif
            execvp(argv[0], argv);
            fprintf(stderr, "%s: execvp: %s\n", progname, strerror(errno));
            _exit(EXIT_FAILURE);
        } else {                        /* parent */
#ifdef REDIRECT
            if (redir_stdin_fd) {
                (void) close(redir_stdin_fd);
            }
            if (redir_stdout_fd) {
                (void) close(redir_stdout_fd);
            }
            if (redir_stderr_fd) {
                (void) close(redir_stderr_fd);
            }
#endif
            if (waitpid(pid, &status, 0) == -1) {
                fprintf(stderr, "%s: waitpid: %s\n", progname, strerror(errno));
            }
        }
    }

    return EXIT_SUCCESS;
}
