/*
CH-230-A
a5_p6.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    scanf("%d", &n);
    float *arr = (float *)malloc(n * sizeof(float));
    float *ptr;
    //ptr=arr;
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &arr[i]);
    }
    for (ptr = &arr[0]; ptr < n + ptr; ptr++)
    {
        if (*ptr < 0)
        {
            printf("Before the first negative value: %ld elements\n", ptr - arr);
            break;
        }
    }
    free(arr);

    return 0;
}
