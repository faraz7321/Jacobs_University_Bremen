#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    //complete the program, using nested loops

    char ch;
    int i, nr;

    //how many elements we have on the current row
    nr = 1;

    //the loop stops after we print the line
    //with n elements
    while (nr <= n)
    {
        //we always start the row from A
        ch = 'A';
        for (i=0; i<nr; i++)
                printf("%c", ch + i);
        printf("\n");

        //we increase nr, preparing it for the next row
        nr++;
    }

    return 0;
}
