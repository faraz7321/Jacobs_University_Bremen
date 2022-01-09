#include "stack.h"
/**
 * @brief pushes an integer to array
 *
 * @param st
 * @param x
 */
void push(Stack *st, int x)
{
    if (st->count >= 12)
    {
        printf("Pushing Stack Overflow\n");
    }
    else
    {
        // printf("%d\n", st->count);
        printf("Pushing %d\n", x);

        st->array[st->count] = x;
        st->count++;

        // printf("%d\n", st->count);
    }
    return;
}
/**
 * @brief remove top element
 *
 * @param st
 */
void pop(Stack *st)
{
    if (st->count <= 0)
    {
        printf("Popping Stack Underflow\n");
    }
    else
    {
        printf("Popping %d\n", st->array[st->count]);
        st->count--;
    }
    return;
}
/**
 * @brief empties the stack
 *
 * @param st
 */
void empty(Stack *st)
{
    int n = st->count;
    if (n <= 0)
    {
        printf("Popping Stack Underflow\n");
        return;
    }
    printf("Emptying Stack ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", st->array[st->count]);
        st->count--;
    }
    printf("\n");
}
/**
 * @brief create empty stack (initialization)
 *
 * @return Stack*
 */
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