/*
CH-230-A
a2_p7.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    int i = 8;
    /*'i' is not a part of the loop as without curly braces
    only statement1 is part of the while loop
    decrement in 'i' should also be a part of while loop
    because its value should be decreased each time the loop runs
    curly braces must be placed to add multiple statements*/
    while (i >= 4)
    {
        printf("i is %d\n", i);
        i--; //decrement in 'i'
    }
    printf("That's it.\n");
    return 0;
}