/*
CH-230-A
a3_p1.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    float x;
    int n;
    scanf("%f", &x);
    /*checking the value of 'x' whether it is
     non zero and positive*/
input:
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Input is invalid, reenter value\n");
        goto input;
    }
    //Printing value of 'x' n times
    while (n > 0)
    {
        printf("%lf\n", x);
        n--;
    }

    return 0;
}