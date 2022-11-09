#include "quiz.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
extern void printScore();
/**
 * @brief plays one iteration of the game
 *
 * @param quiz
 * @return int
 */
int play(quiz_t *quiz)
{
    int pts = 8, answer;
    bool flag = false;
    char *url = "http://numbersapi.com/random/math?min=1&max=100&fragment&json";
    char *json = fetch(url);

    parse(json, quiz);
    printf("\nQ%d: %s\n", quiz->n, quiz->text);
    quiz->max = quiz->max + pts;
    while (!flag)
    {

        printf("%d pt> ", pts);
        scanf("%d", &answer);
        if (answer == quiz->number)
        {
            printf("Congratulation, your answer %d is correct.\n", answer);
            quiz->score = quiz->score + pts;
            flag = true;
        }
        else if (answer > quiz->number)
        {
            printf("Too large, ");
            if (pts == 1)
            {
                printf("the correct answer was %d.\n", quiz->number);
                printScore();
                break;
            }
            else
            {
                printf("try again.\n");
                pts = pts / 2;
                continue;
            }
        }
        else if (answer < quiz->number)
        {
            printf("Too small, ");
            if (pts == 1)
            {
                printf("the correct answer was %d.\n", quiz->number);
                printScore();
                break;
            }
            else
            {
                printf("try again.\n");
                pts = pts / 2;
                continue;
            }
        }

        printScore();
    }
    return 0;
}
