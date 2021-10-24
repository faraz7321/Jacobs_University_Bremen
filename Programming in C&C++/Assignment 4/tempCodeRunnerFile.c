/*
CH-230-A
a4_p9.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
int prodminmax(int arr[], int n)
{
    int i = 0;
    int max = arr[0], min = arr[0];
    while (n--)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        if (arr[i] < min)
        {
            min = arr[i];
        }
        i++;
    }

    //calculating product
    return min * max;
}
int main()
{
    int n;
    printf("Enter size of array= ");
    scanf("%d", &n);
    //Declaring an array of size n
    int *arr = (int *)malloc(n * sizeof(int));
    //taking input into array from user
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Product of min and max= %d\n", prodminmax(arr, n));
    free(arr);
    return 0;
}
