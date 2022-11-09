#include "quiz.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

/* to compile "gcc quiz.c play.c fetch.c parse.c -o quiz -ljson-c" */

quiz_t quiz;

// signal handler
static void sig_handler(int signum);
void menu();
void printScore();

int main()
{
    signal(SIGINT, sig_handler); // Register signal handler
    menu();
    while (true)
    {
        quiz.n++;
        play(&quiz);
    }

    return 0;
}
void menu()
{
    printf("Answer questions with numbers in the range [1..100].\n");
    printf("You score points for each correctly answered question.\n");
    printf("If you need multiple attempts to answer a question, the\n");
    printf("points you score for a correct answer go down.\n");
}

static void sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        fprintf(stderr, "\n\nThanks for playing today.\n");
        printScore();
        exit(signum);
    }
}
void printScore()
{
    printf("Your total score is %d/%d points.\n", quiz.score, quiz.max);
}