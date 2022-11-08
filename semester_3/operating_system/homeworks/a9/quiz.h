/*
 * quiz/quiz.h --
 */
#ifndef QUIZ_H
#define QUIZ_H
typedef struct
{
    unsigned n;     /* current question number (starting at 1) */
    unsigned score; /* current total score */
    unsigned max;   /* possible max score */
    char *text;     /* next question (dynamically allocated) */
    int number;     /* next expected correct answer */
} quiz_t;
/*
 * Fetch the content of the given url by running 'curl' as a child
 * process and reading the response from a pipe. The response is
 * returned as a malloc'ed string, or NULL if there was an error.
 *
 * Implement the fetch() function in a fetch.c module.
 */
extern char *fetch(char *url);
/*
 * Parse a JSON encoded question add fill the next question into the
 * quiz_t. Use a JSON parsing library (e.g., jansson or json-c). The
 * function returns 0 or -1 if there was a parsing error.
 *
 * Implement the parse() function in a parse.c module.
 */
extern int parse(char *json, quiz_t *quiz);
/*
 * Play one round of the quiz game by first fetching and parsing a
 * quiz question and then interacting with the user. The function
 * returns 0 or -1 if there was an error.
 *
 * Implement the play() function in a play.c module.
 */
extern int play(quiz_t *quiz);
#endif
