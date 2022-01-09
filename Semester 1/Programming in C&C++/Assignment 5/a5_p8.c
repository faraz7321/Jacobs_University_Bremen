/*
CH-230-A
a5_p8.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int m, n, p, c, d, k, sum = 0;

    scanf("%d%d%d", &m, &n, &p);

    //Allocating memory for A matrix
    int *A[m];
    for (int i = 0; i < m; i++)
    {
        A[i] = (int *)malloc(n * sizeof(int));
    }

    //Allocating memory for B matrix
    int *B[n];
    for (int i = 0; i < n; i++)
    {
        B[i] = (int *)malloc(p * sizeof(int));
    }

    //Allocating memory for result matrix
    int *result[m];
    for (int i = 0; i < m; i++)
    {
        result[i] = (int *)malloc(p * sizeof(int));
    }

    //input in A matrix
    for (c = 0; c < m; c++)
    {
        for (d = 0; d < n; d++)
        {
            scanf("%d", &A[c][d]);
        }
    }

    //input in B matrix
    for (c = 0; c < n; c++)
    {
        for (d = 0; d < p; d++)
        {
            scanf("%d", &B[c][d]);
        }
    }
    //Multiplication of A x B
    for (c = 0; c < m; c++)
    {
        for (d = 0; d < p; d++)
        {
            for (k = 0; k < p; k++)
            {
                sum = sum + A[c][k] * B[k][d];
            }

            result[c][d] = sum;
            sum = 0;
        }
    }

    //Printing A, B and result matrices

    printf("Matrix A:\n");
    for (c = 0; c < m; c++)
    {
        for (d = 0; d < n; d++)
        {
            printf("%d ", A[c][d]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for (c = 0; c < n; c++)
    {
        for (d = 0; d < p; d++)
        {
            printf("%d ", B[c][d]);
        }
        printf("\n");
    }

    printf("The multiplication result AxB:\n");
    for (c = 0; c < m; c++)
    {
        for (d = 0; d < n; d++)
            printf("%d ", result[c][d]);

        printf("\n");
    }

    //free the dynamically allocated memory
    for (int i = 0; i < m; i++)
    {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < n; i++)
    {
        free(B[i]);
    }

    free(B);
    for (int i = 0; i < m; i++)
    {
        free(result[i]);
    }
    free(result);

    return 0;
}