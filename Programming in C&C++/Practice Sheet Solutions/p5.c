#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool odd(unsigned char data)
{

    if (data & 1 == 1)
        return true;
    else
        return false;

}
int main()
{
    unsigned char ch;
    scanf("%c", &ch);

    if (odd(ch))
        printf("Odd!\n");
    else
        printf("Even!\n");

    return 0;
}
