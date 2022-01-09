/*
CH-230-A
a6_p1.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
//Defining Macro
#define SWAP(x, y, TYPE) \
    {                    \
        TYPE temp;       \
        temp = x;        \
        x = y;           \
        y = temp;        \
    }
/*#define SWAP(x, y) \
    {                    \
        x = x + y;       \
        y = x - y;       \
        x = x - y;       \
    }*/
int main()
{
    int a, b;
    double c, d;
    //taking input from user
    scanf("%d%d%lf%lf", &a, &b, &c, &d);
    printf("After swapping:\n");
    //using macro to swap values in a and b
    SWAP(a, b, int);
    printf("%d\n%d\n", a, b);
    //using macro to swap values in c and d
    SWAP(c, d, double);
    printf("%0.6lf\n%0.6lf\n", c, d);
}