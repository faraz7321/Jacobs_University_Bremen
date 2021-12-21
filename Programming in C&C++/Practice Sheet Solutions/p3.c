#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, *arr;

    //reading the nr of elements
    scanf("%d", &n);

    //dynamically allocating memory
    arr = (int* )malloc(sizeof(int) * n);
    if (arr == NULL)
        exit(1);

    //reading the values and storing them in the array
    for (i=0; i<n; i++)
        scanf("%d", &arr[i]);

    //opening the output file
    FILE *fc;
    fc = fopen("squares.txt", "w");

    //computing the squares and printing them in the file
    //going in reverse order
    for (i=n-1; i>=0; i--)
        fprintf(fc, "%d %d\n", arr[i], arr[i]*arr[i]);

    //freeing the memory
    free(arr);

    //closing the file
    fclose(fc);

    return 0;
}
