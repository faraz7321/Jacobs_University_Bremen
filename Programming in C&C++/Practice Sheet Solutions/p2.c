#include <stdio.h>
#include <stdlib.h>

int main()
{
    double a;
    //reading a double
    scanf("%lf", &a);

    float b;
    //reading a float
    scanf("%f", &b);

    int c;
    //reading an integer
    scanf("%d", &c);

    //no information should be lost, so we use double
    double result;
    result = a * b * c;

    printf("Initial value of result is: %lf\n", result);

    //initializing a pointer to the address of result
    double* r_ptr;
    r_ptr = &result;

    //increasing result by using the pointer
    *r_ptr = *r_ptr + 5;

    printf("Value of result is: %lf\n", result);
    printf("Value of *r_ptr is: %lf\n", *r_ptr);

    return 0;
}
