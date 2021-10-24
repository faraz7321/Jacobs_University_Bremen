/*
CH-230-A
a2_p6.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    double x, y;
    printf("Input 1: ");
    scanf("%lf", &x);
    printf("Input 2: ");
    scanf("%lf", &y);
    double *ptr_one, *ptr_two, *ptr_three;
    //initializing pointers to respective int variables
    ptr_one = &x;
    ptr_two = &x;
    ptr_three = &y;
    //address of ptr one and two is same because they point to the same variable
    printf("Address of ptr_one: %p\n", (void *)ptr_one);
    printf("Address of ptr_two: %p\n", (void *)ptr_two);
    printf("Address of ptr_three: %p\n", (void *)ptr_three);
    return 0;
}