#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    char ch;
    scanf("%d", &n);
    getchar();
    scanf("%c", &ch);
// add your code completion below

    int nr = 1;
    //nr represents the number of elements we have
    //on the current line

    while (nr <= n)
    {
        for (int i=0; i<nr; i++)
            printf("%c", ch);
        printf("\n");

        //increasing nr, preparing it for the next line
        nr++;
    }
    return 0;
}
