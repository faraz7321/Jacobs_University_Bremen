/*
CH-230-A
a4_p2.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <string.h>
int main()
{
    char str[50];

    scanf("%[^\n]%*c", str); //taking input from user
    for (int i = 0; i < strlen(str); i++)
    {
        //to check if i is even or odd
        //prints char with space and newline
        if (i % 2 != 0)
        {
            printf(" %c\n", str[i]);
        }
        //prints char just with a newline
        else
        {
            printf("%c\n", str[i]);
        }
    }

    return 0;
}