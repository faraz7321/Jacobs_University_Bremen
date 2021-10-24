/*
CH-230-A
a3_p11.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <string.h>
#define BUFFER 1024
int main()
{
    char one[BUFFER], two[BUFFER];

    scanf("%[^\n]%*c", one);
    scanf("%[^\n]%*c", two);
    char c;
    c = getchar();
    getchar();
    //printf("%s\n", one);
    //printf("%s\n", two);
    int length1 = strlen(one), length2 = strlen(two);
    printf("length1=%d\n", length1);
    printf("length2=%d\n", length2);
    char concat[BUFFER];
    strcpy(concat, one);
    printf("concatenation=%s\n", strcat(concat, two));
    char three[BUFFER];
    printf("copy=%s\n", strcpy(three, two));
    if (strcmp(one, two) < 0)
    {
        printf("one is smaller than two\n");
    }
    else if (strcmp(one, two) == 0)
    {
        printf("one is equal to two\n");
    }
    else
    {
        printf("one is larger than two\n");
    }

    int position;
    int flag = 0;
    for (int i = 0; i < length2; i++)
    {
        if (two[i] == c)
        {
            position = i;
            flag = 1;
            break;
        }
    }
    if (flag != 0)
    {
        printf("position=%d\n", position);
    }
    else
    {
        printf("The character is not in the string\n");
    }
    return 0;
}