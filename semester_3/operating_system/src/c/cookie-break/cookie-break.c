/*
 * cookie-break/cookie-break.c --
 *
 *	See the assignment #2 of the course Operating Systems, 2014,
 *	offered at Jacobs University Bremen.
 */

#define _REENTRANT
#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>
#include <pthread.h>

static const char *progname = "cookie-break";

typedef struct table {
    int waiting;
    int talker;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
} table_t;

typedef struct ietf {
    int num_tables;
    int num_attendees;
    int num_regular;
    int num_dotted;
    int num_done;
    int wait_time;
    int talk_time;
    int cookie_time;
    int num_talkers;
    table_t *tables;
    pthread_t *reg_attendees;
    pthread_t *dot_attendees;
} ietf_t;

/*
 * Wrapper functions around pthread library calls to simplify the
 * error handling code in the main functions.
 */

static void
my_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		  void *(*start_routine) (void *), void *arg, const char *func)
{
    int err = pthread_create(thread, attr, start_routine, arg);
    if (err) {
	fprintf(stderr, "%s: %s(): unable to create thread: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }
}

static void
my_pthread_join(pthread_t thread, void **retval, const char *func)
{
    if (thread) {
	int err = pthread_join(thread, retval);
	if (err) {
	    fprintf(stderr, "%s: %s(): unable to join thread: %s\n",
		    progname, func, strerror(err));
	}
    }
}

static void
my_pthread_mutex_init(pthread_mutex_t *mutex,
		      const pthread_mutexattr_t *attr, const char *func)
{
    int	err = pthread_mutex_init(mutex, attr);
    if (err) {
	fprintf(stderr, "%s: %s(): unable to initialize mutex: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }
}
    
static void
my_pthread_mutex_lock(pthread_mutex_t *mutex, const char *func)
{
    int err = pthread_mutex_lock(mutex);
    
    if (err) {
	fprintf(stderr, "%s: %s(): unable to lock mutex: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }
}

static int
my_pthread_mutex_timedlock(pthread_mutex_t *mutex,
			   const struct timespec *abs_timeout,
			   const char *func)
{
    int err = pthread_mutex_timedlock(mutex, abs_timeout);
    
    if (err != ETIMEDOUT && err != 0) {
	fprintf(stderr, "%s: %s(): unable to lock mutex: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }
    
    return err;
}

static void
my_pthread_mutex_unlock(pthread_mutex_t *mutex, const char *func)
{
    int err = pthread_mutex_unlock(mutex);
    
    if (err) {
	fprintf(stderr, "%s: %s(): unable to unlock mutex: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }
}

static void
my_pthread_cond_init(pthread_cond_t *cond,
		     const pthread_condattr_t *attr, const char *func)
{
    int err = pthread_cond_init(cond, attr);

    if (err) {
	fprintf(stderr, "%s: %s(): unable to initialize condition variable: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }
}

static int
my_pthread_cond_timedwait(pthread_cond_t *cond,
			  pthread_mutex_t *mutex,
			  const struct timespec *abs_timeout,
			  const char *func)
{
    int err = pthread_cond_timedwait(cond, mutex, abs_timeout);
    
    if (err != ETIMEDOUT && err != 0) {
	fprintf(stderr, "%s: %s(): unable to wait for condition: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }

    return err;
}

static void
my_pthread_cond_signal(pthread_cond_t *cond, const char *func)
{
    int err = pthread_cond_signal(cond);
    
    if (err) {
	fprintf(stderr, "%s: %s(): unable to signal condition: %s\n",
		progname, func, strerror(err));
	exit(EXIT_FAILURE);
    }
}

/*
 * Pick a random table. Pretty trivial, no?
 */

static int
pick_table(ietf_t *ietf)
{
    return random() % ietf->num_tables;
}

/*
 * Entry point for threads representing regular attendees.
 */

static void*
regular_life(void *data)
{
    int t, err, talk;
    struct timespec timeout;
    ietf_t *ietf = (ietf_t *) data;

    assert(ietf);

try_table:
    clock_gettime(CLOCK_REALTIME , &timeout);
    timeout.tv_sec += ietf->wait_time;
    
    t = pick_table(ietf);
    
    fprintf(stderr, "** regular attendee arriving at table %d\n", t);
    err = my_pthread_mutex_timedlock(&ietf->tables[t].mutex, &timeout, __func__);
    if (err == ETIMEDOUT) {
	fprintf(stderr, "** regular attendee walking to another table\n");
	goto try_table;
    }
    
    ietf->tables[t].waiting++;
    while (ietf->tables[t].waiting > 1 && ietf->tables[t].talker == 0) {
	fprintf(stderr, "** %d attendees waiting at table %d\n", ietf->tables[t].waiting, t);
	err = my_pthread_cond_timedwait(&ietf->tables[t].cond,
					&ietf->tables[t].mutex,
					&timeout, __func__);
	if (err == ETIMEDOUT) {
	    fprintf(stderr, "** regular attendee walking to another table\n");
	    ietf->tables[t].waiting--;
	    my_pthread_mutex_unlock(&ietf->tables[t].mutex, __func__);
	    goto try_table;
	}
    }
    talk = (ietf->tables[t].talker > 0);
    if (talk) {
	ietf->tables[t].waiting--;
	ietf->tables[t].talker--;
    }
    my_pthread_mutex_unlock(&ietf->tables[t].mutex, __func__);

    if (talk) {
	fprintf(stderr, "** engaging in a hallway talk at table %d\n", t);
	sleep(ietf->talk_time);
	goto try_table;
    }

    fprintf(stderr, "** YUMMI - grabbin cookies at table %d\n", t);
    sleep(ietf->cookie_time);
    fprintf(stderr, "** YUMMI - one cookie less at table %d\n", t);

    my_pthread_mutex_lock(&ietf->tables[t].mutex, __func__);
    ietf->tables[t].waiting--;
    if (ietf->tables[t].waiting == 0) {
	ietf->tables[t].talker = 0;
    }
    ietf->num_done++;				/* XXX race condition */
    my_pthread_cond_signal(&ietf->tables[t].cond, __func__);
    my_pthread_mutex_unlock(&ietf->tables[t].mutex, __func__);

    fprintf(stderr, "** regular attendee leaving table %d\n", t);

    return NULL;
}

/*
 * Entry point for threads representing dotted attendees.
 */

static void*
dotted_life(void *data)
{
    int t, cont = 1;
    ietf_t *ietf = (ietf_t *) data;

    assert(ietf);

    while (cont) {
	t = pick_table(ietf);
	fprintf(stderr, "** dotted attendee arriving at table %d\n",t );
	my_pthread_mutex_lock(&ietf->tables[t].mutex, __func__);
	ietf->tables[t].talker = ietf->num_talkers;
	for (int i = 0; i < ietf->num_talkers; i++) {
	    my_pthread_cond_signal(&ietf->tables[t].cond, __func__);
	}
	cont = (ietf->num_done < ietf->num_regular);
	my_pthread_mutex_unlock(&ietf->tables[t].mutex, __func__);
	sleep(ietf->talk_time);
    }
	
    return NULL;
}

/*
 * Create threads for all regular and dotted attendees and join them
 * back when they are all done eating and chatting.
 */

static int
coffee_break(ietf_t *ietf)
{
    assert(ietf);

    for (int i = 0; i < ietf->num_tables; i++) {
	my_pthread_mutex_init(&ietf->tables[i].mutex, NULL, __func__);
	my_pthread_cond_init(&ietf->tables[i].cond, NULL, __func__);
    }

    for (int i = 0; i < ietf->num_regular; i++) {
	my_pthread_create(&(ietf->reg_attendees[i]), NULL,
			  regular_life, ietf, __func__);
    }

    for (int i = 0; i < ietf->num_dotted; i++) {
	my_pthread_create(&(ietf->dot_attendees[i]), NULL,
			  dotted_life, ietf, __func__);
    }

    for (int i = 0; i < ietf->num_regular; i++) {
	my_pthread_join(ietf->reg_attendees[i], NULL, __func__);
    }

    for (int i = 0; i < ietf->num_dotted; i++) {
	my_pthread_join(ietf->dot_attendees[i], NULL, __func__);
    }

    return EXIT_SUCCESS;
}

int
main(int argc, char *argv[])
{
    int c;
    
    ietf_t ietf = {
	.num_tables = 3,
	.num_attendees = 100,
	.num_dotted = 5,
	.wait_time = 5,
	.talk_time = 3,
	.cookie_time = 1,
	.num_talkers = 4,
	.tables = NULL,
	.reg_attendees = NULL,
	.dot_attendees = NULL,
    };

    while ((c = getopt(argc, argv, "t:n:d:w:s:c:m:h")) >= 0) {
        switch (c) {
        case 't':
            if ((ietf.num_tables = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of tables must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'n':
            if ((ietf.num_attendees = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of attendees must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            if ((ietf.num_dotted = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of dotted attendees must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'w':
            if ((ietf.wait_time = atoi(optarg)) <= 0) {
                fprintf(stderr, "maximum wait time must be > 0\n");
                exit(EXIT_FAILURE);
            }
	    break;
        case 's':
            if ((ietf.talk_time = atoi(optarg)) <= 0) {
                fprintf(stderr, "talk time must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'c':
            if ((ietf.cookie_time = atoi(optarg)) <= 0) {
                fprintf(stderr, "cookie pickup time must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'm':
            if ((ietf.num_talkers = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of talkers must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            printf("Usage: %s [-t tables] [-n attendees] [-d dotted] [-w wait] [-s talk-time] [-c cookie-time] [-m talkers] [-h]\n", progname);
            exit(EXIT_SUCCESS);
        }
    }

    ietf.num_regular = ietf.num_attendees - ietf.num_dotted;
    if (ietf.num_regular <= 0) {
	fprintf(stderr, "number of regular attendees must be > 0\n");
	exit(EXIT_FAILURE);
    }

    ietf.tables = calloc(ietf.num_tables, sizeof(table_t));
    ietf.reg_attendees = calloc(ietf.num_regular, sizeof(pthread_t));
    ietf.dot_attendees = calloc(ietf.num_dotted, sizeof(pthread_t));

    if (! ietf.tables
	|| ! ietf.reg_attendees
	|| ! ietf.dot_attendees) {
	fprintf(stderr, "%s: %s\n", progname, strerror(errno));
	exit(EXIT_FAILURE);
    }

    coffee_break(&ietf);

    if (ietf.tables) free(ietf.tables);
    if (ietf.reg_attendees) free(ietf.reg_attendees);
    if (ietf.dot_attendees) free(ietf.dot_attendees);

    return EXIT_SUCCESS;
}
