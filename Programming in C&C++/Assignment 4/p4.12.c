#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
int main()
{
    char str[80];
    char e, c;
    while (1)
    {
        fgets(str, 80, stdin); // taking input
        //enter stop to end program
        if (strcmp(str, "stop\n") == 0)
        {
            return 0;
        }
        c = getchar();
        getchar();
        e = getchar();
        getchar();
        replaceAll(str, c, e);
        printf("%s\n", str);
    }
    return 0;
}
