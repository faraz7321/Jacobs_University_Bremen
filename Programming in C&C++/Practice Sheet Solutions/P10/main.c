#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **A, int rows, int cols)
{
    for (int i=1; i<=rows; i++)
    {
        for (int j=1; j<=cols; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}
int main()
{
    int r,c, **A, i, j;

    //opening the reading file
    FILE *fp;
    fp = fopen("matrix.dat", "r");
    if (fp == NULL)
        exit(1);

    //reading the nr of rows and columns from the file
    fscanf(fp, "%d %d", &r, &c);

    //dynamically allocating memory
    A = (int**)malloc(sizeof(int*) * r);
    if (A == NULL)
        exit(1);
    for (i=1; i<=r; i++)
    {
        A[i] = (int*)malloc(sizeof(int) * c);
        if (A[i] == NULL)
            exit(1);
    }

    //setting all values of the matrix with 0
    for (i=1; i<=r; i++)
        for(j=1; j<=c; j++)
            A[i][j] = 0;

    //reading the matrix values
    int x, y, z;
    while (!feof(fp))
    {
        fscanf(fp, "%d %d %d", &x, &y, &z);
        A[x][y] = z;
    }

    print_matrix(A, r, c);

    //freeing the memory
    for (i=1; i<=c; i++)
        free(A[i]);
    free(A);

    return 0;
}
