#include <stdio.h>
#include <stdlib.h>
void binary(unsigned char ch)
{
    unsigned int mask = 128;
    int x;
    while (mask > 0)
    {
        x = ch & mask;
        if (x == 0)
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
int main()
{
    unsigned char ch;
    //taking input from user
    scanf("%c", &ch);

    printf("The decimal representation is: %d\n", ch);
    printf("The binary representation is: ");
    //prints binary
    binary(ch);
    return 0;
}