/*
CH-230-A
a2_p8.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    int input;
    scanf("%d", &input);
    /*input is checked whether it is fully
    divisible by 2 and 7 or not by using modulus==0*/
    if (input % 2 == 0 && input % 7 == 0)
    {
        printf("The number is divisible by 2 and 7\n");
    }
    else
    {
        printf("The number is NOT divisible by 2 and 7\n");
    }

    return 0;
}