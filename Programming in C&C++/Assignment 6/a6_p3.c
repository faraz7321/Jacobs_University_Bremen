/*
CH-230-A
a6_p3.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
//Defining macros
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CHECK_1(a, b) MIN(a, b)
#define CHECK_2(b, c) MIN(b, c)
#define MINIMUM(a, b, c) MIN(MIN(a, b), (c)) //gives mminimum of 3 numbers
#define MAXIMUM(a, b, c) MAX(MAX(a, b), (c)) //gives maximum of 3 numbers
int main()
{
    int a, b, c;
    //taking input from user
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    int min = MINIMUM(a, b, c);          //returns minimun
    int max = MAXIMUM(a, b, c);          //returns maximun
    double mid = (float)(min + max) / 2; //calculating mid value

    printf("The mid-range is: %0.6lf\n", mid);
    return 0;
}
