/*
CH-230-A
a4_p12.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void replaceAll(char *str, char c, char e);
int main()
{
    char str[80];
    char e, c;
input:
    printf("Enter string: ");
    fgets(str, 80, stdin); // taking input
    //printf("%s\n", str);
    //this will end program if user enters "stop"
    if (strcmp(str, "stop\n") == 0)
    {
        return 0;
    }

    //taking input from user
    printf("c= ");
    scanf(" %c", &c);
    getchar();

    printf("e= ");
    scanf(" %c", &e);
    getchar();

    //Calling function to perform operations
    replaceAll(str, c, e);
    printf("New string= %s\n", str);
    goto input; //loop back
    return 0;
}
/**
 * @brief replaces c character with e in string
 * 
 * @param str 
 * @param c 
 * @param e 
 */
void replaceAll(char *str, char c, char e)
{
    for (int i = 0; i < 80; i++)
    {
        if (str[i] == c)
        {
            str[i] = e;
        }
    }
}