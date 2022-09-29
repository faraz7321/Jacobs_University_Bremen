#include <iostream>
using namespace std;
void print(int arr[], int n);
int findMax(int arr[], int n);
void countingSort(int arr[], int n, int exp);
void radixSort(int arr[], int n);

int main()
{
    int n;
    int arr[] = {142, 378, 583, 314, 860, 413, 387, 314, 777};
    n = sizeof(arr) / sizeof(int);
    cout << "Unsorted version of the array: " << endl;
    print(arr, n);
    cout << endl;
    cout << "Sorted version of the array: " << endl;
    radixSort(arr, n);
    print(arr, n);

    return 0;
}

/**
 * @brief printing elements
 *
 * @param arr
 * @param n
 */
void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/**
 * @brief fining max in array
 *
 * @param arr
 * @param n
 * @return int
 */
int findMax(int arr[], int n)
{
    int mx = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > mx)
            mx = arr[i];
    }
    return mx;
}

/**
 * @brief implementing count sort using
 * simple exponent
 *
 * @param arr
 * @param n
 * @param exp
 */
void countingSort(int arr[], int n, int exp)
{
    int output[n];
    const int m = findMax(arr, n) + 1;
    int C[m];
    for (int i = 0; i < m; i++)
    {
        C[i] = 0;
    }

    for (int i = 0; i < n; i++)
        C[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        C[i] += C[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[C[(arr[i] / exp) % 10] - 1] = arr[i];
        C[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

/**
 * @brief implemeting Radix Sort
 *
 * @param arr
 * @param n
 */
void radixSort(int arr[], int n)
{
    int m = findMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        countingSort(arr, n, exp);
    }
}
// source : geeksforgeeks