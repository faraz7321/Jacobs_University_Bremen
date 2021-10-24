/*
CH-230-A
a5_p5.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>
double scalerProduct(double *v, double *w, int n);
double smallest(double *arr, int n);
double largest(double *arr, int n);
int position(double *arr, int n, double x);
int main()
{
    int n;

    //taking input from user
    scanf("%d", &n);

    //initializing array
    double *v = (double *)malloc(n * sizeof(double));
    double *w = (double *)malloc(n * sizeof(double));

    //taking input from user in v
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &v[i]);
    }

    //taking input from user in w
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &w[i]);
    }

    printf("Scalar product=%lf\n", scalerProduct(v, w, n));

    //assigning return values of functions to variables
    double s, l;
    s = smallest(v, n);
    l = largest(v, n);
    //printing for v
    printf("The smallest = %lf\n", s);
    printf("Position of smallest = %d\n", position(v, n, s));
    printf("The largest = %lf\n", l);
    printf("Position of largest = %d\n", position(v, n, l));

    //printing for w
    s = smallest(w, n);
    l = largest(w, n);
    printf("The smallest = %lf\n", s);
    printf("Position of smallest = %d\n", position(w, n, s));
    printf("The largest = %lf\n", l);
    printf("Position of largest = %d\n", position(w, n, l));
    return 0;
}
/**
 * @brief calculates scaler product of v and w
 * 
 * @param v 
 * @param w 
 * @param n 
 * @return double 
 */
double scalerProduct(double *v, double *w, int n)
{
    double scalerProduct = 0;
    for (int i = 0; i < n; i++)
    {
        scalerProduct = scalerProduct + (v[i] * w[i]);
    }
    return scalerProduct;
}
/**
 * @brief calculates smallest element in array
 * 
 * @param arr1 
 * @param n 
 * @return double 
 */
double smallest(double *arr1, int n)
{
    double temp, s;
    double *arr2 = (double *)malloc(n * sizeof(double));

    //copying elements of arr1 into arr2
    for (int i = 0; i < n; i++)
    {
        arr2[i] = arr1[i];
    }
    //sorting elements in arr2
    for (int i = 0; i < (n - 1); ++i)
    {
        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (arr2[j] > arr2[j + 1])
            {
                temp = arr2[j + 1];
                arr2[j + 1] = arr2[j];
                arr2[j] = temp;
            }
        }
    }
    s = arr2[0];
    free(arr2);
    return s;
}
/**
 * @brief calculates largest element in array
 * 
 * @param arr1 
 * @param n 
 * @return double 
 */
double largest(double *arr1, int n)
{
    double temp, l;
    double *arr2 = (double *)malloc(n * sizeof(double));

    //copying elements of arr1 into arr2
    for (int i = 0; i < n; i++)
    {
        arr2[i] = arr1[i];
    }
    //sorting elements in arr2
    for (int i = 0; i < (n - 1); ++i)
    {
        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (arr2[j] > arr2[j + 1])
            {
                temp = arr2[j + 1];
                arr2[j + 1] = arr2[j];
                arr2[j] = temp;
            }
        }
    }
    l = arr2[n - 1];
    free(arr2);
    return l;
}
/**
 * @brief calculates position of an element in array
 * 
 * @param arr 
 * @param n 
 * @param x 
 * @return int 
 */
int position(double *arr, int n, double x)
{
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            index = i;
            return i;
        }
    }

    return index;
}