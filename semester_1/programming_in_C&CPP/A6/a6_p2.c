/*
CH-230-A
a6_p2.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
//Macro which return 0 or 1
#define LSB(ch, mask, lsb) (((ch) & (mask)) == 0 ? (lsb = 0) : (lsb = 1))

int main()
{
    unsigned char ch;
    unsigned int mask = 128; //using 8 bits for ASCII
    //taking input from user
    scanf("%c", &ch);
    getchar();
    printf("The decimal representation is: %d\n", ch);
    int lsb;

    while (mask > 0)
    {
        mask = mask >> 1; // Right Shift
        if (mask == 1)
        {
            //prints right most(least significant) bit
            printf("The least significant bit is: %d\n", LSB(ch, mask, lsb));
        }
    }

    return 0;
}