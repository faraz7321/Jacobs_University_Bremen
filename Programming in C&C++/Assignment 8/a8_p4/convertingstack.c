/*
CH-230-A
convertingstack.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "stack.h"

int main()
{
    Stack *st = init(); // initializing stack
    unsigned int x;
    int n, i = 0, temp;
    scanf("%d", &n);
    x = n;
    // converting unsigned int to binary
    while (n > 0)
    {
        // storing remainder in stack
        temp = n % 2;
        push(st, temp);
        n = n / 2;
        i++;
    }

    // printing binary
    printf("The binary representation of %d is ", x);
    empty(st);
    return 0;
}