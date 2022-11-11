/* 
 * snake/main.c --
 *
 * This file implements the main function of the snake game. It also
 * defines all the functions that deal with the environment.
 */

#define _POSIX_C_SOURCE 2

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include <signal.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <curses.h>

#include "snake.h"

const char *progname = "snake";

static int oldcur = 0;

static snake_t *snake;

static volatile sig_atomic_t exit_in_progress = 0;

/*
 * The signal handler which is used to regular timer trap as well as
 * trap to terminate the program.
 */

static void
handler(int signum)
{
    switch (signum) {
    case SIGALRM:
	snake_move(snake);
	break;

    default:
	if (exit_in_progress) {
	    raise(signum);
	    return;
	}
	exit_in_progress = 1;
	snake_exit_curses();
        snake_delete(snake);
	signal(signum, SIG_DFL);
	raise(signum);
	break;
    }
}

/*
 * Abort the program after printing an error message. The format
 * is a typical printf() format string.
 */

void
snake_panic(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    fputs(progname, stderr);
    fputs(": ", stderr);
    vfprintf(stderr, format, ap);
    fputs("\n", stderr);
    exit(EXIT_FAILURE);
}

/*
 * Get the current size of the terminal. This function uses a specific
 * ioctl which might not be available on all platforms.
 */

void
snake_get_term_size(int *rows, int *cols)
{
    struct winsize ws;

    if (ioctl(0, TIOCGWINSZ, &ws) == -1) {
	snake_panic("ioctl failed: %s", strerror(errno));
    }
    
    *rows = ws.ws_row;
    *cols = ws.ws_col;
}

/*
 * We need a timer signal every us microseconds.
 */

static void
init_timer(long us)
{
    struct itimerval it;

    it.it_interval.tv_sec  = 0;
    it.it_interval.tv_usec = us;
    it.it_value.tv_sec	   = 0;
    it.it_value.tv_usec    = us;
    if (setitimer(ITIMER_REAL, &it, NULL) == -1) {
	snake_panic("setitimer failed: %s", strerror(errno));
    }
}

/*
 * Catch the timer signals and the signals that terminate the process
 * so that we can leave the terminal in a usable state.
 */

static void
init_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags   = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGILL,  &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    sigaction(SIGALRM, &sa, NULL);

    sa.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &sa, NULL);
}

/*
 * Initialize curses. Keep a copy of the current curser status so that
 * it can be restored when the program leaves curses.
 */

void
snake_init_curses(void)
{
    if (initscr() == NULL) {
        snake_panic("initscr() failed");
    }
    cbreak();			/* */
    noecho();			/* turn off character echo */
    keypad(stdscr, TRUE);	/* enable the keypad (function keys */
    intrflush(stdscr, FALSE);	/* */
    oldcur = curs_set(0);	/* make curser invisible */
    clear();
    box(stdscr, 0, 0);
}

/*
 * Exit curses. Restore the curser to the previously saved state.
 */

void
snake_exit_curses(void)
{
    delwin(stdscr);
    curs_set(oldcur);
    endwin();
}

/*
 * Terminate the snake program with a suitable goodbye message.
 */

void
snake_exit(int reason, char *msg)
{
    snake_exit_curses();

    switch (reason) {
    case SNAKE_EXIT_HITWALL:
        printf("You hit a wall!\n");
        printf("Your score is %d\n", snake->score);
        break;

    case SNAKE_EXIT_HITSELF:
        printf("You ran into yourself!\n");
        printf("Your score is %d\n", snake->score);
        break;

    case SNAKE_EXIT_ERROR:
	snake_delete(snake);
	snake_panic("%s", msg);
	break;

    default:
        printf("Goodbye!\n");
        break;
    }

    snake_delete(snake);
    exit(EXIT_SUCCESS);
}

/*
 * And here we go. The option parsing can still be improved...
 */

int
main(int argc, char **argv)
{
    int c;
    int len = 5;
    long us = 200000;
    int food = 1;
    char *usage = "Usage: %s [-f food] [-l len] [-t us] [-v]\n";

    while ((c = getopt(argc, argv, "hf:l:t:v")) >= 0) {
        switch (c) {
        case 'h':
            printf(usage, progname);
            exit(EXIT_SUCCESS);
        case 'v':
            printf("%s version 0.0.1\n", progname);
            exit(EXIT_SUCCESS);
        case 'f':
	    food = atoi(optarg);	/* xxx */
            break;
        case 'l':
            len = atoi(optarg);		/* xxx */
            break;
        case 't':
	    us = atol(optarg);		/* xxx */
            break;
        case ':':
        case '?':
            exit(1);
        }
    }

    if (argc != optind) {
	fprintf(stderr, usage, progname);
	return EXIT_FAILURE;
    }

    init_signals();
    init_timer(us);
    snake_init_curses();

    srand((unsigned) time(NULL));

    snake = snake_create(len);
    for (int i = 0; i < food; i++) {
	snake_food(snake);
    }
    snake_draw(snake);

    while (1) {
        switch (c = getch()) {
	case 'i':
        case KEY_UP:
	    snake_direction(snake, SNAKE_DIRECTION_UP);
            break;
	case 'k':
        case KEY_DOWN:
	    snake_direction(snake, SNAKE_DIRECTION_DOWN);
            break;
	case 'j':
        case KEY_LEFT:
	    snake_direction(snake, SNAKE_DIRECTION_LEFT);
            break;
	case 'l':
        case KEY_RIGHT:
	    snake_direction(snake, SNAKE_DIRECTION_RIGHT);
	    break;
        }
    }

    snake_exit_curses();
    snake_delete(snake);

    return EXIT_SUCCESS;
}
