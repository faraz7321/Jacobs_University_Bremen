/*
CH-230-A
a6_p6.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    unsigned char ch;
    //taking input from user
    scanf("%c", &ch);
    unsigned int mask = 128; //mask = [1000 0000] or 8 bits
    printf("The decimal representation is: %d\n", ch);
    printf("The binary representation is: ");
    //prints binary equivalent of ASCII of ch
    while (mask > 0)
    {
        if ((ch & mask) == 0)
        {
            printf("0");
        }
        else
        {
            printf("1");
        }
        mask = mask >> 1; // Right Shift
    }
    printf("\n");
    return 0;
}