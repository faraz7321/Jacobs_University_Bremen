#include <iostream>
using namespace std;
void mergeSort(int *arr, int low, int high, int k);
void print(int *arr, int size);
void insertionSort(int *arr, int size);
void merge(int *arr, int low, int high, int mid);
int main()
{
    int const size = 10;
    int k = 3;
    int arr[size] = {10, 9, 8, 7, 1, 2, 5, 6, 4, 3};
    cout << "before: ";
    print(arr, size);
    mergeSort(arr, 0, size - 1, k);
    cout << "\nafter:  ";
    print(arr, size);
    return 0;
}
void mergeSort(int *arr, int low, int high, int k)
{
    int mid;
    if (high + 1 <= k)
    {
        insertionSort(arr, high + 1);
        return;
    }
    if (high + 1 == k)
    {
        return;
    }
    if (low < high)
    {
        // divide the array at mid and sort independently using merge sort
        mid = (low + high) / 2;
        mergeSort(arr, low, mid, k);
        mergeSort(arr, mid + 1, high, k);
        // merge or conquer sorted arrays
        merge(arr, low, high, mid);
    }
}

void merge(int *arr, int low, int high, int mid)
{
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
        {
            c[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        arr[i] = c[i];
    }
}
void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void insertionSort(int *arr, int size)
{
    int key = 0;
    int i = 0;
    for (int j = 1; j < size; j++)
    {
        key = arr[j];
        i = j - 1;
        while (i >= 0 && arr[i] > key)
        {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}