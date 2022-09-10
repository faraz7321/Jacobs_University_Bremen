/*
CH-230-A
a3_p9.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Function prototype
double sum25(double v[], int n);
int main()
{
    int n;
    int arr_length;
    scanf("%d", &n);
    /*to initialize an array which has n elements
     but also no more than 20 elements*/
    if (n > 20)
    {
        arr_length = 20;
    }
    else
    {
        arr_length = n;
    }
    double arr[arr_length];
    //taking input from user in array
    for (int i = 0; i < arr_length; i++)
    {
        scanf("%lf", &arr[i]);
    }
    double sum = sum25(arr, arr_length);
    if (sum == -111.000000)
    {
        //printf("sum=%lf\n", sum);
        printf("One or both positions are invalid\n");
    }
    else
    {
        printf("sum=%lf\n", sum);
    }

    return 0;
}
/**
 * @brief calculate sum of values on 
 * index 2 and 5 in array v
 * 
 * @param v 
 * @param n 
 * @return double 
 */
double sum25(double v[], int n)
{
    double sum = 0;
    if (n < 6)
    {
        return -111;
    }
    else
    {
        sum = v[2] + v[5];
        return sum;
    }
}