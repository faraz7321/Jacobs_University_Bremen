/*
CH-230-A
a6_p5.c
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
    printf("The decimal representation is: %d\n", ch);
    printf("The backwards binary representation is: ");
    int i = 0;

    while ((1 << i) <= ch) //left shift
    {                      //printing the bit 0 or 1
        printf("%d", (ch >> i) & 1);
        i = i + 1;
    }
    printf("\n");
    return 0;
}