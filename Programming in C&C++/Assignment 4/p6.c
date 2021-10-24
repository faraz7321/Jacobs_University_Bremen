/*
CH-230-A
a4_p6.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
void greatest_values(int arr[], int size);
int main()
{
    int n; // size of array
    printf("Enter size of array: ");
    scanf("%d", &n);
    //Declaring an array of size n
    int *arr = (int *)malloc(n * sizeof(int));
    //taking input into array from user
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    //Calling the function
    greatest_values(arr, n);
    //freeing memory
    free(arr);
    return 0;
}
/**
 * @brief this function first sort an array and the print 
 * two largest values in it
 * 
 * @param arr 
 * @param size 
 */
void greatest_values(int arr[], int size)
{
    int i, j, temp;
    //Sorting the array in acending order
    for (i = 0; i < (size - 1); ++i)
    {
        for (j = 0; j < size - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    //highest number = last element of the sorted array
    //second highest number = second last element of the sorted array
    printf("Highest number in array= %d\n", arr[size - 1]);
    printf("Second highest number in array= %d\n", arr[size - 2]);
}