/*
CH-230-A
a5_p2.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
void divby5(float arr[], int size);
int main()
{
    //initializing array
    float arr[] = {5.5, 6.5, 7.75, 8.0, 9.6, 10.36};
    //Printing element of the array before division
    printf("Before:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%0.3f ", arr[i]);
    }
    //calling the function to perform operation
    divby5(arr, 6);
    //printitng the array after division
    printf("\nAfter:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%0.3f ", arr[i]);
    }
    printf("\n");
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