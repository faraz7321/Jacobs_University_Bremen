/*
CH-230-A
a5_p9.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
void printMatrix(int ***p, int rows, int columns, int depth);
int main()
{
    int ***p = NULL, rows, columns, depth;
    //taking input of size of array from user
    scanf("%d%d%d", &rows, &columns, &depth);

    //decalring 3D dynamic array
    p = (int ***)malloc(rows * sizeof(int **));
    if (p == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        p[i] = (int **)malloc(columns * sizeof(int *));
        if (p[i] == NULL)
        {
            exit(1);
        }
        for (int j = 0; j < columns; j++)
        {
            p[i][j] = (int *)malloc(depth * sizeof(int));
            if (p[i][j] == NULL)
            {
                exit(1);
            }
        }
    }
    //taking input in 3D array
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            for (int k = 0; k < depth; k++)
            {
                scanf("%d", &p[i][j][k]);
            }
        }
    }
    //calling function to print the array with blocks
    printMatrix(p, rows, columns, depth);

    //free dynamically allocated memory
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            free(p[i][j]);
        }
        free(p[i]);
    }
    free(p);
    return 0;
}
/**
 * @brief printing array in blocks
 * 
 * @param p 
 * @param rows 
 * @param columns 
 * @param depth 
 */
void printMatrix(int ***p, int rows, int columns, int depth)
{
    int count = 1; //counts number of sections/blocks
    printf("Section %d:\n", count);
    //printing elements of array
    for (int k = 0; k < depth; k++)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                printf("%d ", p[i][j][k]);
            }
            printf("\n");
        }
        if (k < depth - 1)
        {
            count++;
            printf("Section %d:\n", count);
        }
    }
}