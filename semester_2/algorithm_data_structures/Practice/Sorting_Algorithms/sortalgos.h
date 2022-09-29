/*
 * CH-231-1
 * sortalgos.h
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 */

#include <iostream>
#include <cstdlib>
#include <time.h>

// Function prototype ////////////////////////////

void insertionSort(int *arr, int n);
void mergeSort(int *arr, int low, int high);
void selectionSort(int *arr, int size);
void heapSort();
void merge(int *arr, int low, int high, int mid);
int *initArray(int size);
void swap(int *a, int *b);
void print(int *A, int size);

// Function implementaion ///////////////////////

/**
 * @brief initializes array
 *
 * @param arr
 * @param size
 */
int *initArray(int size)
{
    srand((unsigned)time(NULL));
    int *arr = new int[size];
    // generating n random numbers
    // storing them in arrays a, b, c
    for (int i = 0; i < size; i++)
    {
        int key = rand() % 101;
        arr[i] = key;
    }
    return arr;
}
/**
 * @brief Insertion Sort Algorithm
 *
 * @param arr
 * @param size
 */
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
/**
 * @brief Merge Sort Algorithm
 *
 * @param arr
 * @param low
 * @param high
 */
void mergeSort(int *arr, int low, int high)
{
    int mid;
    if (low < high)
    {
        // divide the array at mid and sort independently using merge sort
        mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        // merge or conquer sorted arrays
        merge(arr, low, high, mid);
    }
}

/**
 * @brief Utility function to mergeSort
 *
 * @param arr
 * @param low
 * @param high
 * @param mid
 */
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
/**
 * @brief Utility function to selectionSort
 *
 * @param a
 * @param b
 */
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief Selection Sort Algorithm
 *
 * @param arr
 * @param size
 */
void selectionSort(int *arr, int size)
{
    int min_idx;
    for (int i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            swap(&arr[min_idx], &arr[i]);
        }
    }
}