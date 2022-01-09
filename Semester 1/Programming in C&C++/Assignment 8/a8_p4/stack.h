/*
CH-230-A
stack.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
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
/**
 * @brief pushes element into stack
 *
 * @param st
 * @param x
 */
void push(Stack *st, int x);
/**
 * @brief pop an element from stack
 *
 * @param st
 */
void pop(Stack *st);
/**
 * @brief checks if the stack is empty
 *
 * @param st
 */
void isEmpty(Stack *st);
/**
 * @brief empties the stack
 *
 * @param st
 */
void empty(Stack *st);
/**
 * @brief initializes a stack
 *
 * @return Stack*
 */
Stack *init(void);