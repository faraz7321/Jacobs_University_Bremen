/*
CH-230-A
testqueue.c
Faraz Ahmad
fahmad@jacobs.university.de
 */

/**
 * @file testqueue.c
 */
#include "queue.h"

int main()
{
    Queue line;
    Item temp;
    char ch;

    initialize_queue(&line);

    while (((ch = getchar()) != EOF) && (ch != 'q'))
    {
        switch (ch)
        {
        case 'a':
            printf("add int: ");
            scanf("%d", &temp);
            if (!queue_is_full(&line))
            {
                printf("Putting %d into queue\n", temp);
                enqueue(temp, &line);
            }
            else
                puts("Queue is full");
            break;

        case 'd':
            if (queue_is_empty(&line))
                puts("Nothing to delete!");
            else
            {
                /*
                the variable temp still stores the input value in the beginning
                of case 'a' so i moved the dequeue function in printf where it
                it returns an integer value (dequeue int)
                */
                printf("Removing %d from queue\n", dequeue(&temp, &line));
            }
            break;

        default:
            printf("%d items in queue\n", queue_item_count(&line));
            puts("Type a to add, d to delete, q to quit:");
        }
    }
    empty_queue(&line);
    puts("Bye.");
    return 0;
}