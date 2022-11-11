/*
 * snake/snake.h
 *
 * This file defines the interface for a snake. 
 */

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "dlist.h"

/*
 * A snake consists of an ordered list of parts and the current
 * running direction.
 */

#define SNAKE_DIRECTION_DOWN  1
#define SNAKE_DIRECTION_UP    2
#define SNAKE_DIRECTION_LEFT  3
#define SNAKE_DIRECTION_RIGHT 4

#define SNAKE_CHAR_SNAKE	'#'	/* character for the snake */
#define SNAKE_CHAR_FOOD		'*'	/* character for snake food */
#define SNAKE_CHAR_EMPTY	' '	/* character for an empty place */

typedef struct snake_part {
    int x;			/* x coordinate of the snake part */
    int y;			/* y coordinate of the snake part */
} snake_part_t;

typedef struct snake {
    int cols;			/* number of columns on terminal */
    int rows;			/* number of rows on terminal */
    int direction;		/* current direction of the snake */
    int score;			/* current score of the snake */
    dlist_t *parts;		/* parts of a snake */
} snake_t;

extern snake_t*
snake_create(int len);

extern void
snake_delete(snake_t *snake);

extern void
snake_draw(snake_t *snake);

extern void
snake_move(snake_t *snake);

extern void
snake_direction(snake_t *snake, int direction);

extern void
snake_food(snake_t *snake);

/*
 * Function to initialize and exit curses, to get the current terminal
 * size and to exit the life of the snake (and the snake application).
 */

extern void
snake_exit_curses(void);

extern void
snake_init_curses(void);

extern void
snake_get_term_size(int *rows, int *cols);

#define SNAKE_EXIT_USER		1
#define SNAKE_EXIT_HITSELF      2
#define SNAKE_EXIT_HITWALL      3
#define SNAKE_EXIT_ERROR	4

extern void
snake_exit(int reason, char *msg);

extern void
snake_panic(const char *format, ...);

#endif
