/*
CH-230-A
a6_p4.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
#define INTERMEDIATE
int main()
{
    int n, scalarProd = 0;
    scanf("%d", &n); //size of vector

    //declaring vectors on size n
    int *vector1 = (int *)malloc(n * sizeof(int));
    int *vector2 = (int *)malloc(n * sizeof(int));
    int *inter = (int *)malloc(n * sizeof(int));

    //taking input in vector from user
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vector1[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vector2[i]);
    }
    //calculates intermediate value and scalar product
    for (int i = 0; i < n; i++)
    {
        inter[i] = vector1[i] * vector2[i];
        scalarProd = scalarProd + inter[i];
    }
    //checking if the micro is defined
#if defined(INTERMEDIATE)
    printf("The intermediate product values are:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", inter[i]);
    }

#endif
    {
        printf("The scalar product is: %d\n", scalarProd);
    }
    //deallocating memeory
    free(vector1);
    free(vector2);
    free(inter);
    return 0;
}