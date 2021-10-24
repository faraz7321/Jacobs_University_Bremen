/*
CH-230-A
a6_p7.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned char set3bits(unsigned char ch, int x, int y, int z);
void toBinary(unsigned char ch, unsigned int mask);
int main()
{
    unsigned char ch;
    unsigned int mask = 128; //mask = [1000 0000] or 8 bits
    int x, y, z;             //bit positions

    //taking input from user
    scanf("%c", &ch);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);
    printf("The decimal representation is: %d\n", ch);
    printf("The binary representation is: ");
    toBinary(ch, mask); //prints binary

    printf("After setting the bits: ");
    ch = set3bits(ch, x, y, z); //changes the unsigned char accoriding to bit positions
    toBinary(ch, mask);         //printing binary after changing
    return 0;
}
/**
 * @brief set bit to 1 at bit position 
 * of given parameters
 * 
 * @param ch 
 * @param x 
 * @param y 
 * @param z 
 * @return unsigned char 
 */
unsigned char set3bits(unsigned char ch, int x, int y, int z)
{
    ch = ch | (int)pow(2, x);
    ch = ch | (int)pow(2, y);
    ch = ch | (int)pow(2, z);
    return ch;
}
/**
 * @brief converts and prints unsigned char to binary
 * 
 * @param ch 
 * @param mask 
 */
void toBinary(unsigned char ch, unsigned int mask)
{
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
}
