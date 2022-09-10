/*
CH-230-A
a1_p6.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    char c = 'F';
    printf("c= %c\n", c);
    int x = c + 3; //increment
    c = x;         //assigning char corresponding to the ASCII
    printf("after increment c= %c\n", c);
    printf("ASCII code of new character= %d\n", x);
}