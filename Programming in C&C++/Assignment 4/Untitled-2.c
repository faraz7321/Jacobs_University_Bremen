/*
CH-230-A
a5_p1.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
void print(int n, char ch)
{
    for (int i = n; i >= 1; --i)
    {
        for (int j = 1; j <= i; ++j)
        {
            printf("%c", ch);
        }
        printf("\n");
    }
}
int main()
{
    int n;
    char ch;
    //taking input from user
    scanf("%d", &n);
    scanf(" %c", &ch);
    getchar();
    //calling function to print tiangle
    print(n, ch);
    return 0;
}
