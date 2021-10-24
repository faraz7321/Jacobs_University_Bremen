/*
CH-230-A
a7_p7.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "stack.h"

int main()
{
    // create a stack of capacity 5
    Stack *st = init();
    int x;
    char ch;
    do
    {
        // taking input from user
        scanf(" %c", &ch);
        getchar();
        switch (ch)
        {
            // push
        case 's':
        {
            scanf("%d", &x); // integer to push into stack
            push(st, x);
            break;
        }
        // pop
        case 'p':
        {
            pop(st);
            break;
        }
        // empties the stack
        case 'e':
        {
            empty(st);
            break;
        }
        // quit program
        case 'q':
        {
            printf("Quit\n");
            free(st);
            exit(0);
            break;
        }
        default:
            // printf("Quit\n");
            break;
        }

    } while (1);
    printf("\n");
    return 0;
}
