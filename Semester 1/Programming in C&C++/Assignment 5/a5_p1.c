/*
CH-230-A
a5_p1.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
void print(int n, char ch);
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
/**
 * @brief this function prints a triangle of height n
 * and of char c
 * 
 * @param n 
 * @param ch 
 */
void print(int n, char ch)
{
    int N = n;
    for (int i = 0; i < n; i++)
    {
        N = n - i;
        while (N != 0)
        {
            printf("%c", ch);
            N--;
        }
        printf("\n");
    }
}