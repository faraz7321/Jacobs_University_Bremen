/*
CH-230-A
a3_p8.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Function prototype
float sum(float arr[], int size);
float average(float Sum, int size);
int main()
{
    float arr[10];
    int count = 0; //to calculate length of array
    /*takes input from the user till end of array
    or stop taking input when user enter -99*/
    for (int i = 0; i < 10; i++)
    {
        scanf("%f", &arr[i]);
        if (arr[i] != -99.0)
        {
            count++;
            continue;
        }
        else
        {
            break;
        }
    }
    printf("%d\n", count);
    float Sum = sum(arr, count);
    printf("Sum: %f\n", Sum);
    printf("Average: %f\n", average(Sum, count));
    return 0;
}
/**
 * @brief calculate sum of a and b
 * 
 * @param arr 
 * @param size 
 * @return float 
 */
float sum(float arr[], int size)
{
    float Sum = 0;
    for (int i = 0; i < size; i++)
    {
        Sum = Sum + arr[i];
    }
    return Sum;
}
/**
 * @brief calculate average on float values in a string
 * 
 * @param Sum 
 * @param size 
 * @return float 
 */
float average(float Sum, int size)
{
    float avg = 0;
    avg = (float)Sum / size;
    return avg;
}