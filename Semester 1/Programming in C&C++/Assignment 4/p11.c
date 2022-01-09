/*
CH-230-A
a4_p11.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int count_insensitive(char *str, char c);
int main()
{
    char *input = (char *)malloc(50 * sizeof(char));
    fgets(input, 50, stdin);
    int length = strlen(input);
    char *str = (char *)malloc(length * sizeof(char));
    strcpy(str, input);
    // printf("%d\n", length);
    // printf("%s\n", str);
    char ch[] = {'b', 'H', '8', 'u', '$'};
    free(input);
    printf("%s\n", str);
    for (int i = 0; i < sizeof(ch); i++)
    {
        printf("The character '%c' occurs %d times\n", ch[i], count_insensitive(str, tolower(ch[i])));
    }

    return 0;
}
int count_insensitive(char *str, char c)
{
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (tolower((unsigned char)str[i]) == c)
        {
            count++;
        }
    }

    return count;
}