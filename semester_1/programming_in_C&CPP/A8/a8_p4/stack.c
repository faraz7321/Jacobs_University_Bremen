/*
CH-230-A
stack.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "stack.h"

void push(Stack *st, int x)
{
    if (st->count >= 12)
    {
        printf("Pushing Stack Overflow\n");
    }
    else
    {
        // printf("Pushing %d\n", x);
        st->count++;
        st->array[st->count] = x;
    }
    return;
}
void pop(Stack *st)
{
    if (st->count <= 0)
    {
        printf("Popping Stack Underflow\n");
    }
    else
    {
        printf("%d", st->array[st->count]);
        st->count--;
    }
    return;
}
void empty(Stack *st)
{
    int n = st->count;
    if (n <= 0)
    {
        printf("Popping Stack Underflow\n");
        return;
    }
    // printf("Emptying Stack ");
    for (int i = 0; i < n; i++)
    {
        printf("%d", st->array[st->count]);
        st->count--;
    }
    printf("\n");
}
Stack *init(void)
{
    Stack *st = malloc(sizeof(*st));
    if (st == NULL)
    {
        exit(EXIT_FAILURE);
    }
    st->count = 0;
    return st;
}