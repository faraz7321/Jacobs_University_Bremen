/*
 * expect/expect.c --
 *
 *      This program demonstrates the usage of pseudoterminals by
 *      implementing a very much simplified version of expect.
 */

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <regex.h>

#include <readline/readline.h>
#include <readline/history.h>

static int interactive = 1;

/*
 * Spawn a child process executing argv[] with stdin, stdout, and
 * stderr directed to the terminal device of a pseudoterminal device
 * pair. Return the file descriptor for the pseudoterminal device or
 * -1 on error.
 */

static int
spawn(int argc, char *argv[])
{
    int pty, tty;
    char *ttyname;
    pid_t pid;

    (void) argc;
    pty = open("/dev/ptmx", O_RDWR);
    if (! pty) {
	(void) perror("open()");
	return -1;
    }

    /* get the name of the terminal device of the pseudoterminal device pair */
    ttyname = ptsname(pty);
    if (! ttyname) {
	perror("ptsname()");
	(void) close(pty);
	return -1;
    }
    
    /* grant access to the terminal device */
    if (grantpt(pty) == -1) {
	perror("grantpt()");
	(void) close(pty);
	return -1;
    }

    /* unlock the pseudoterminal device pair */
    if (unlockpt(pty) == -1) {
	perror("unlockpt()");
	(void) close(pty);
	return -1;
    }

    /* open the terminal device of the pseudoterminal device pair */
    tty = open(ttyname, O_RDWR);
    if (! tty) {
	perror("open()");
	(void) close(pty);
	return -1;
    }

    pid = fork();
    if (pid == -1) {
	perror("fork()");
	(void) close(pty);
	(void) close(tty);
	return -1;
    }

    if (pid == 0) {
	(void) dup2(tty, STDIN_FILENO);
        (void) dup2(tty, STDOUT_FILENO);
	(void) dup2(tty, STDERR_FILENO);
	(void) close(pty);
	(void) close(tty);
	(void) execvp(argv[0], argv);
	perror("execvp()");
	exit(EXIT_FAILURE);
    } else {
	(void) close(tty);
    }

    return pty;
}

/*
 * Read lines from pseudoterminal device until there is is a line
 * matching the pattern or there is no more input (end of file).
 */

static void
expect(FILE *pty, const char *pattern)
{
    int rc;
    char buf[2048];
    regex_t preg;

    rc = regcomp(&preg, pattern, REG_EXTENDED | REG_NOSUB);
    if (rc != 0) {
	regerror(rc, &preg, buf, sizeof(buf));
	fprintf(stderr, "regcomp(): %s\n", buf);
	return;
    }

    while (1) {
	char *line = NULL;
	size_t len = 0;

	rc = getline(&line, &len, pty);
	if (rc == -1) {
	    perror("getline()");
	    exit(EXIT_FAILURE);
	}
	if (rc == 0) {
	    break;
	}
        
        if (rc && line[rc-1] == '\n') {
            line[rc-1] = 0;
            rc--;
        }
        if (rc && line[rc-1] == '\r') {
            line[rc-1] = 0;
            rc--;
        }

	if (interactive) {
	    fprintf(stderr, "recv: >%s<\n", line);
	}

	rc = regexec(&preg, line, 0, NULL, 0);
	if (rc != 0 && rc != REG_NOMATCH) {
	    regerror(rc, &preg, buf, sizeof(buf));
	    fprintf(stderr, "regexec(): %s\n", buf);
	    regfree(&preg);
	}

	if (line) free(line);

	if (rc == 0) {
	    break;
	}
    }

    regfree(&preg);
}

/*
 * Send a message via the pseudoterminal device to the terminal device.
 */

static void
send(FILE *pty, const char *msg)
{
    int rc;
    
    rc = fprintf(pty, "%s\n", msg);
    if (rc < 0) {
	perror("fprintf()");
    }
    (void) fflush(pty);
    if (interactive) {
	fprintf(stderr, "send: >%s<\n", msg);
    }
}

/*
 * Read commands like
 * 
 *   expect .*assword.*
 *   send secret
 *   quit
 * 
 * do drive a dialogue with a spawned command.
 */

void
chat(FILE *input, FILE *pty)
{
    char *cmd, *arg;
    char *prompt = "(expect) ";

    interactive = isatty(fileno(input));

    while (1) {
	char *line = NULL;
	size_t len = 0;

        if (interactive) {
            line = readline(prompt);
	    if (line == NULL) {
		break;
	    }
        } else {
            ssize_t rc;
            rc = getline(&line, &len, input);
            if (rc == -1) {
                perror("getline()");
                exit(EXIT_FAILURE);
            }
            if (rc == 0) {
                break;
            }
            if (rc && line[rc-1] == '\n') {
                line[rc-1] = 0;
            }
        }

        if (interactive) {
            add_history(line);
        }
	cmd = line;
	arg = line;
	while (*arg && ! isspace(*arg)) arg++;
	if (*arg) {*arg = '\0'; arg++;}
	if (strcmp(cmd, "expect") == 0) {
	    expect(pty, arg);
	} else if (strcmp(cmd, "send") == 0) {
	    send(pty, arg);
	} else if (strcmp(cmd, "quit") == 0) {
	    return;
	} else {
	    fprintf(stderr, "expect: unknown command '%s'\n", cmd);
	}
	if (line) free(line);
    }
}

static int
run(const char *filename, FILE *pty)
{
    FILE *input;
    
    if (! filename || strcmp(filename, "-") == 0) {
	filename = "/dev/tty";
    }
    input = fopen(filename, "r+");
    if (! input) {
	perror("fopen()");
	return -1;
    }

    chat(input, pty);

    if (fflush(input) || ferror(input)) {
	perror("fflush() or ferror()");
	exit(1);
    }
    (void) fclose(input);

    return 0;
}

int
main(int argc, char **argv)
{
    FILE *pty;
    int fd;

    (void) argc;
    fd = spawn(argc - 1, argv + 1);
    if (fd == -1) {
	return EXIT_FAILURE;
    }
    if (NULL == (pty = fdopen(fd, "r+"))) {
        perror("fdopen()");
        return EXIT_FAILURE;
    }
    setbuf(pty, NULL);
    run(NULL, pty);
    (void) fclose(pty);
    
    return EXIT_SUCCESS;
}
