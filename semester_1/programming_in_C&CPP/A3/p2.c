/*
CH-230-A
a3_p2.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    char ch;
    int x;
    //taking input from user
    printf("Enter a character: ");
    ch = getchar();
    getchar();
    printf("Enter an integer: ");
    scanf("%d", &x);
    printf("Output: ");
    //Printing comma seperated characters with 1 decrement
    for (int i = 0; i < x; i++)
    {
        if (i < x - 1)
        {
            printf("%c", ch - i);
            printf(", ");
        }
        //this way comma is not printing at the last eg c, b, a,
        else
        {
            printf("%c", ch - i);
            break;
        }
    }

    return 0;
}