/*
CH-230-A
a4_p5.[c or cpp or h]
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
 * @brief count the number of consonants in string using pointer
 * 
 * @param str 
 * @return int 
 */
int count_consonants(char str[])
{
    //declaring and initializing a pointer
    char *ptr;
    ptr = str;

    int consonants = 0;
    for (int i = 0; i < strlen(str); i++)

    { //checks if char is an alphabet
        if ((*ptr >= 65 && *ptr <= 90) || (*ptr >= 97 && *ptr <= 122))
        {
            //check if char is a vowel
            if (*ptr == 'a' || *ptr == 'e' || *ptr == 'i' || *ptr == 'o' || *ptr == 'u' || *ptr == 'A' || *ptr == 'E' || *ptr == 'I' || *ptr == 'O' || *ptr == 'U')
            {
                ptr++;
            }
            else
            {
                ptr++; //moves to next index
                consonants++;
            }
        }
        else
        {
            ptr++;
        }
    }

    return consonants;
}