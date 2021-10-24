/*
CH-230-A
a1_p2.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    int result; /* The result of our calculation */
    result = (2 + 7) * 9 / 3;

    /*printf("The result is %d\n"); Garbage value will
    be printed as the variable 'result' is not specified 
    in the printf second parameter. We told the function
    that we are going to print a decimal but did not specify
    what variable to print*/

    printf("The result is %d\n", result); //new statement
    return 0;
}