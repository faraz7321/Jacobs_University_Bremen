#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
int main()
{
    char *input = (char *)malloc(50 * sizeof(char));
    fgets(input, 50, stdin);
    char s;
    char *str = (char *)malloc(strlen(input) * sizeof(char));
    strcpy(str, input);
    char carr[] = {'b', 'H', '8', 'u', '$'};
    free(input);
    printf("%s\n", str);
    for (int i = 0; i < sizeof(carr); i++)
    {
        s = tolower(carr[i]);
        printf("The character '%c'", carr[i]);
        printf(" occurs %d", count_insensitive(str, s));
        printf(" times\n");
    }
    return 0;
}
