/*
 * hello/hello-ncurses.c --
 *
 *	A hello world program using the [n]curses library.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

static void cleanup()
{
    endwin();
}

int main(void)
{
    const char *spin[] = { "o<", "o-", NULL };
    const char *msg = "Hello, world!";
    WINDOW *win;
    int c, y, x, my, mx;

    if ((win = initscr()) == NULL) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }
    atexit(cleanup);

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    my = LINES/2, mx = COLS/2 - strlen(msg)/2;

    for (y = 0; y < my; y++) {
	mvaddstr(y, mx, msg);
	refresh(); napms(100);
	move(y, mx); clrtoeol();
    }
    mvaddstr(my, mx, msg);
    refresh();
    for (x = 0; (c = getch()) == ERR && x < (int) (mx + strlen(msg)); x++) {
	mvaddstr(my, x, spin[x%2]);
	refresh(); napms(100);
	mvaddch(my, x, ' ');
    }
    for (y = my; y < LINES; y++) {
	mvaddstr(y, x, "oo");
	refresh(); napms(100);
	move(y, x); clrtoeol();
    }
    delwin(win);

    return EXIT_SUCCESS;
}
