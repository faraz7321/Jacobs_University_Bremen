/*
 * CH-231-1
 * driver.cpp
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 */

#include "sortalgos.h"
using namespace std;

int main()
{
    int *arr = NULL; //array pointer.
    int n = 30; // size of array.
    arr = initArray(n);
    cout << "Original array:\n";
    print(arr, n);
    //selectionSort(arr, n);
    //mergeSort(arr, 0, n - 1);
    cout << "\nSorted array:\n";
    print(arr, n);

    return 0;
}
void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
