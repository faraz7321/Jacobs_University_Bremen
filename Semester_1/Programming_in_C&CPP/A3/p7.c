/*
CH-230-A
a3_p7.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Function prototype
void print_form(int n, int m, char c);
int main()
{
    int m, n;
    scanf("%d", &n);
    scanf("%d", &m);
    char c;
    scanf(" %c", &c);
    print_form(n, m, c);
    // printf("%d%d%c", n, m, c);

    return 0;
}
/**
 * @brief This function prints trapezoid with
 * height n and bases m and m+n-1
 * 
 * @param n 
 * @param m 
 * @param c 
 */
void print_form(int n, int m, char c)
{
    for (int i = 0; i < n; i++) //this loop runs n times for height
    {
        for (int j = 0; j < m; j++)
        /*prints char in a line m times
        then m+1 upto m+n-1*/
        {
            printf("%c", c);
        }
        printf("\n");
        m = m + 1; /*increment in m to print 1 more char
        so a trapezoid can be formed*/
    }
}