/*
CH-230-A
a5_p4.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
void divby5(float arr[], int size);
int main()
{
    int n;
    //taking input from user
    scanf("%d", &n);
    //initializing array
    float *arr = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &arr[i]);
    }
    //Printing element of the array before division
    printf("Before:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%0.3f ", arr[i]);
    }
    //calling the function to perform operation
    divby5(arr, n);
    //printitng the array after division
    printf("\nAfter:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%0.3f ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
/**
 * @brief this function divided all elements of array by 5
 * 
 * @param arr 
 * @param size 
 */
void divby5(float arr[], int size)
{
    for (int i = 0; i < 6; i++)
    {
        arr[i] = arr[i] / 5.0;
    }
}