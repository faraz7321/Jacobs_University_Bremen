/*
CH-230-A
a2_p10.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    int n, hours = 24, i = 0;
input:
    printf("Enter an integer: ");
    scanf("%d", &n);
    /*input is checked here whether it is nonzero
    and a positive integer. If its not then user is asked
    again for an input and keep asking for it until the 
    program gets a valid input*/
    if (n <= 0)
    {
        goto input;
    }

    while (i <= n - 1)
    {
        //to get seperate output for "day" and "days"
        if (i <= 0)
        {
            i++;
            printf("%d", i);
            printf(" day = %d", i * hours);
            printf(" hours\n");
        }
        else
        {
            i++;
            printf("%d", i);
            printf(" days = %d", i * hours);
            printf(" hours\n");
        }
    }

    return 0;
}