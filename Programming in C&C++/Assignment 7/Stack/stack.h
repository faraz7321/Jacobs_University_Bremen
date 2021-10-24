#include <stdio.h>
#include <stdlib.h>

// Data structure to represent a stack
typedef struct stack Stack;
struct stack
{
    unsigned int count;
    int array[12];
};
// Utility function to initialize the stack
void push(Stack *st, int x);
void pop(Stack *st);
void isEmpty(Stack *st);
void empty(Stack *st);
Stack *init(void);