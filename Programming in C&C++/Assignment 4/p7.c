/*
CH-230-A
a4_p7.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
void print(int arr[30][30], int n);
int main()
{
    int n;
    //taking input of size of array from the user
    scanf("%d", &n);
    if (n >= 30)
    {
        n = 30;
    }
    //printf("%d\n", n);
    int arr[30][30];
    //input to array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    // calling function to print matrix
    print(arr, n);
    printf("Under the main diagonal:\n");
    //printing elements under main diagonal in array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > j)
            {
                printf("%d ", arr[i][j]);
            }
        }
    }
    printf("\n");
    return 0;
}
/**
 * @brief prints the 2D array in matrix form
 * 
 * @param arr 
 * @param n 
 */
void print(int arr[30][30], int n)
{
    printf("The entered matrix is:");
    for (int i = 0; i < n; i++)
    {
        printf("\n");
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
    }
    printf("\n");
}