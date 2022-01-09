/*
CH-230-A
a3_p4.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Function prototype
int position(char str[], char c);
int main()
{
    char line[80];
    while (1)
    {
        printf("Enter string: ");
        fgets(line, sizeof(line), stdin);
        //index for first occurence of g will be printed
        printf("The first occurrence of 'g' is: %d\n", position(line, 'g'));
    }
}
/**
 * @brief tell the position of first occurence
 of a character in a string
 * 
 * @param str 
 * @param c 
 * @return int 
 */
int position(char str[], char c)
{
    int idx, count = 0;
    /* Loop until end of string */
    for (idx = 0; str[idx] != '\0'; ++idx)
    {
        if (str[idx] == c && str[idx] != '\0')
        {
            count = idx;
        }
    }
    return count;
}