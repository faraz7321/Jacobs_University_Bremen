#include <stdio.h>
#include <stdlib.h>

void product(double *v, double *w, int n)
{
    double prod;
    for (int i = 0; i < n; i++)

    {
        prod = prod + (v[i] * w[i]);
    }
    printf("Scalar product=%lf\n", prod);
    // calculating the product //
    // printing scalar product as a float //
}
void pos(double *arr, int n, double x, char string[50])
{
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            printf("%s%d\n", string, i);
        }
    }
}
double calculateSmallest(double *arr, int n)
{
    char s1[] = "Position of smallest = ";
    double small;

    /*code to calculate smallest*/
    printf("The smallest = \n", small);
    pos(arr, n, small, s1);
}
double calculateLargest(double *arr, int n)
{
    char s1[] = "Position of largest = ";
    double small;

    /*code to calculate largest*/
    printf("The largest = \n", small);
    pos(arr, n, small, s1);
}
int main()
{
    double *v;
    double *w;
    int n;

    char s2[] = "Position of largest ";
    scanf("%d", &n);
    v = (double *)malloc(sizeof(double) * n);
    w = (double *)malloc(sizeof(double) * n);
    // declaring n as an integer and v, w as components of vectors //
    for (int i = 0; i < n; i++)

    {
        scanf("%lf", &v[i]);
    }
    for (int i = 0; i < n; i++)

    {
        scanf("%lf", &w[i]);
    }
    product(v, w, n);
    calculateSmallest(v, n);
    calculateLargest(v, n);
    calculateSmallest(w, n);
    calculateLargest(w, n);
    return 0;
}
