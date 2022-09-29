/*
CH-230-A
a5_p3.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <string.h>
#include <stdio.h>
int count_lower(char *str);
int main()
{
    char input[50];
    char *str;
    str = input;
    while (1) //Loop goes on until user enters 'ENTER'
    {

        fgets(input, sizeof(input), stdin);
        if (*str == '\n')
        {
            break;
        }

        printf("Number of lowercase char in input= %d\n", count_lower(str));
    }

    return 0;
}
/**
 * @brief count the number of lower case char
 * in string input
 * 
 * @param str 
 * @return int 
 */
int count_lower(char *str)
{
    int count = 0;
    int length = strlen(str);

    //calculates number of lowercase char
    for (int i = 0; i < length; i++)
    {
        if (*str >= 'a' && *str <= 'z')
        {
            count++;
            str++;
        }
        else
        {
            str++;
        }
    }
    return count;
}