/*
 * snake/snake.c --
 *
 * Implementation of the snake.
 */

#include <stdlib.h>
#include <curses.h>
#include <assert.h>

#include "snake.h"

static void*
snake_malloc(size_t size)
{
    void *p = malloc(size);
    if (! p) {
	snake_panic("malloc failed: out of memory");
    }
    return p;
}

snake_t*
snake_create(int len)
{
    snake_t *snake;
    snake_part_t *part;

    assert(len > 0);

    snake = snake_malloc(sizeof(snake_t));
    snake_get_term_size(&snake->rows, &snake->cols);
    snake->score = 0;
    snake->direction = SNAKE_DIRECTION_RIGHT;
    snake->parts = NULL;

    if (len > snake->cols-4) {
	len = snake->cols-4;
    }

    for (int i = 0; i < len; i++) {
	part = snake_malloc(sizeof(snake_part_t));
	part->x = 2 + i;
	part->y = 2;
	snake->parts = dlist_append(snake->parts, part);
    }

    return snake;
}

static void
free_part(void *data, void *unused)
{
    (void) unused;
    free(data);
}

void
snake_delete(snake_t *snake)
{
    if (snake) {
	dlist_foreach(snake->parts, free_part, NULL);
	dlist_delete(snake->parts);
	free(snake);
    }
}

void
snake_draw(snake_t *snake)
{
    dlist_t *elem;
    snake_part_t *part;

    assert(snake);

    for (elem = snake->parts; elem; elem = dlist_next(snake->parts, elem)) {
	part = dlist_data(elem);
	move(part->y, part->x);
	addch(SNAKE_CHAR_SNAKE);
    }
    refresh();
}

void
snake_food(snake_t *snake)
{
    int x, y;
    
    assert(snake);

    do {
        x = (rand() % (snake->cols - 2)) + 1;
        y = (rand() % (snake->rows - 2)) + 1;
        move(y, x);
    } while (inch() != SNAKE_CHAR_EMPTY);

    addch(SNAKE_CHAR_FOOD);
}

void
snake_move(snake_t *snake)
{
    int x, y, c;
    snake_part_t *head, *tail;

    assert(snake && snake->parts);

    head = dlist_data(dlist_last(snake->parts));

    assert(head);

    /* compute the next head position */

    x = head->x, y = head->y;
    switch (snake->direction) {
    case SNAKE_DIRECTION_DOWN:
	y += 1;
	break;
    case SNAKE_DIRECTION_UP:
	y -= 1;
	break;
    case SNAKE_DIRECTION_RIGHT:
	x += 1;
	break;
    case SNAKE_DIRECTION_LEFT:
	x -= 1;
	break;
    }

    /* check what is currently on the next head position and either
       move the snake, eat or report an error condition */
    
    move(y, x);
    switch (c = inch()) {

    case SNAKE_CHAR_EMPTY:
	tail = dlist_data(snake->parts);
	snake->parts = dlist_remove(snake->parts, tail);
	mvaddch(tail->y, tail->x, SNAKE_CHAR_EMPTY);
	head = tail;
	head->x = x, head->y = y;
	snake->parts = dlist_append(snake->parts, head);
	mvaddch(head->y, head->x, SNAKE_CHAR_SNAKE);
	refresh();
	break;

    case SNAKE_CHAR_FOOD:
	head = snake_malloc(sizeof(snake_part_t));
	head->x = x, head->y = y;
	snake->parts = dlist_append(snake->parts, head);
	mvaddch(head->y, head->x, SNAKE_CHAR_SNAKE);
	snake->score += 10;
	snake_food(snake);
	refresh();
	break;

    case SNAKE_CHAR_SNAKE:
	snake_exit(SNAKE_EXIT_HITSELF, NULL);
	break;

    default:
	snake_exit(SNAKE_EXIT_HITWALL, NULL);
	break;
    }
}

void
snake_direction(snake_t *snake, int direction)
{
    assert(snake && (direction == SNAKE_DIRECTION_LEFT
		     || direction == SNAKE_DIRECTION_RIGHT
		     || direction == SNAKE_DIRECTION_UP
		     || direction == SNAKE_DIRECTION_DOWN));

    snake->direction = direction;
    snake_move(snake);
}
