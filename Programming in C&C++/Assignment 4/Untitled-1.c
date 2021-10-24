#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void replaceAll(char *str, char c, char e);
int main()
{
    char str[80];
    char e, c;
    do
    {
        printf("Enter string: ");
        fgets(str, 80, stdin);
        //printf("%s\n", str);
        printf("c= ");
        scanf(" %c", &c);
        getchar();

        printf("e= ");
        scanf(" %c", &e);
        getchar();

        replaceAll(str, c, e);
        printf("New string= %s\n", str);
    } while (str != "stop\n");

    return 0;
}
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