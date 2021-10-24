/*
CH-230-A
a4_p4.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <string.h>
int count_consonants(char str[]);
int main()
{
    char str[100];
input:
    fgets(str, sizeof(str), stdin);

    //if user press enter without giving input in string the program ends
    if (str[0] == '\n')
    {
        return 0;
    }
    else
    {
        printf("Number of consonants=%d\n", count_consonants(str));
        goto input; //loop
    }

    return 0;
}
/**
 * @brief counts number of consonants in a string input
 * 
 * @param str 
 * @return int 
 */
int count_consonants(char str[])
{
    int consonants = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        //checks if char is an alphabet
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
        {
            //check if char is a vowel
            if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
            {
            }
            else
            {
                consonants++;
            }
        }
    }

    return consonants;
}