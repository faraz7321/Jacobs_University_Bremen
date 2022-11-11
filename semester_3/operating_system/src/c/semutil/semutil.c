/*
 * semutil/semutil.c --
 *
 *	A simple wrapper around the POSIX semaphore API for named
 *	semaphores. It allows to create (-c) or open (-o) a named
 *	semaphore and to read its value (-v), to post it (-p), or to
 *	wait for it (-w). The unlink option (-u) removes the name of
 *	the named semaphore and hence no other process can open it
 *	anymore. The name of the semaphore can be specified with the
 *	-n option (it defaults to the program name).
 */

#define _POSIX_C_SOURCE 201112L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#ifdef _POSIX_NAME_MAX
#define SEM_NAME_MAX _POSIX_NAME_MAX
#else
#define SEM_NAME_MAX 127
#endif
static char sem_name[SEM_NAME_MAX];

static const char progname[] = "semutil";
static const char usage[] =
    "Usage: %s [-c] [-o] [-v] [-w] [-p] [-u] [-n name] [-h] ...\n";

static
void sem_open_check(sem_t *s)
{
    if (s == NULL) {
	fprintf(stderr, "%s: semaphore not open\n", progname);
	exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    sem_t *s = NULL;
    int c, val;

    (void) snprintf(sem_name, sizeof(sem_name), "/%s", progname);
    
    while ((c = getopt(argc, argv, "hcovwpun:")) >= 0) {
        switch (c) {
        case 'h':
            printf(usage, progname);
            exit(EXIT_SUCCESS);
	case 'c':
	    s = sem_open(sem_name, O_CREAT, S_IRUSR | S_IWUSR, 0);
	    if (s == SEM_FAILED) {
		perror("sem_open()");
		return EXIT_FAILURE;
	    }
	    printf("semaphore \"%s\" created/opened\n", sem_name);
	    break;
	case 'o':
	    s = sem_open(sem_name, 0);
	    if (s == SEM_FAILED) {
		perror("sem_open()");
		return EXIT_FAILURE;
	    }
	    printf("semaphore \"%s\" opened\n", sem_name);
	    break;
	case 'v':
	    sem_open_check(s);
	    if (-1 == sem_getvalue(s, &val)) {
		perror("sem_getvalue()");
		return EXIT_FAILURE;
	    }
	    printf("semaphore \"%s\" value = %d\n", sem_name, val);
	    break;
	case 'w':
	    sem_open_check(s);
	    printf("semaphore \"%s\" wait ... ", sem_name);
	    fflush(stdout);
	    if (-1 == sem_wait(s)) {
		perror("sem_wait()");
		return EXIT_FAILURE;
	    }
	    printf("done\n");
	    break;
	case 'p':
	    sem_open_check(s);
	    if (-1 == sem_post(s)) {
		perror("sem_post()");
		return EXIT_FAILURE;
	    }
	    printf("semaphore \"%s\" post\n", sem_name);
	    break;
	case 'u':
	    sem_open_check(s);
	    if (-1 == sem_unlink(sem_name)) {
		perror("sem_unlink()");
		return EXIT_FAILURE;
	    }
	    printf("semaphore \"%s\" unlinked\n", sem_name);
	    break;
	case 'n':
	    (void) snprintf(sem_name, sizeof(sem_name), "%s%s",
			    optarg[0] == '/' ? "" : "/", optarg);
	    printf("semaphore name set to \"%s\"\n", sem_name);
	    break;
        case ':':
        case '?':
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
