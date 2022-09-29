/*
CH-230-A
a4_p9.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
int prodminmax(int arr[], int n);
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
/**
 * @brief this function calculates and return 
 * product of minimum and maximum number in the array
 * 
 * @param arr 
 * @param n 
 * @return int 
 */
int prodminmax(int arr[], int n)
{
    int prod = 1;
    int i, j, temp;
    //Sorting the array in acending order
    for (i = 0; i < (n - 1); ++i)
    {
        for (j = 0; j < n - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    //calculating product
    prod = arr[0] * arr[n - 1];
    return prod;
}