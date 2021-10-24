/*
CH-230-A
a7_p5.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>
// FUNCTION DECLARATION
int accending(const void *a, const void *b);
int decending(const void *a, const void *b);
void print_int_array(int *array, int n);
int main()
{
    int n, *arr;
    char ch;

    // pointers to functions
    void (*func1)(int *, int);
    int (*func2)(const void *, const void *);

    func1 = print_int_array;

    // taking input from user
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    while (1)
    {

        scanf(" %c", &ch);
        getchar();
        // sort array in accending order
        if (ch == 'a')
        {
            func2 = accending;
            qsort(arr, n, sizeof(int), func2);
            func1(arr, n);
        }
        // sort array in decending order
        else if (ch == 'd')
        {
            func2 = decending;
            qsort(arr, n, sizeof(int), func2);
            func1(arr, n);
        }
        // end program
        else if (ch == 'e')
        {
            free(arr);
            exit(0);
        }
    }

    return 0;
}
/**
 * @brief //sort array in accending order
 *
 * @param a
 * @param b
 * @return int
 */
int accending(const void *a, const void *b)
{
    const int *ia = (const int *)a; // casting pointer types
    const int *ib = (const int *)b;
    return *ia - *ib;
    /* integer comparison: returns negative if b > a
    and positive if a > b */
}
/**
 * @brief //sort array in decending order
 *
 * @param a
 * @param b
 * @return int
 */
int decending(const void *a, const void *b)
{
    const int *ia = (const int *)a; // casting pointer types
    const int *ib = (const int *)b;
    return *ib - *ia;
    /* integer comparison: returns negative if b > a
    and positive if a > b */
}
/**
 * @brief prints the elements of the array
 *
 * @param array
 * @param n
 */
void print_int_array(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}