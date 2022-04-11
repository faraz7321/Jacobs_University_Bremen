#include <string>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define RANGE 255

void countSort(char *arr)
{
    /*The output character array
    that will have sorted arr*/
    char output[strlen(arr)];

    /*Create a count array to store count of individual
    characters and initialize count array as 0*/
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));

    // Store count of each character
    for (i = 0; arr[i]; ++i)
    {
        ++count[arr[i]];
    }

    /*Change count[i] so that count[i] now contains actual
    position of this character in output array*/
    for (i = 1; i <= RANGE; ++i)
    {
        count[i] += count[i - 1];
    }
    for (i = 0; arr[i]; ++i)
    {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }
    // for stable algorithm
    for (i = sizeof(arr) - 1; i >= 0; --i)
    {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    // Copy the output array to arr, so that arr now
    // contains sorted characters
    for (i = 0; arr[i]; ++i)
    {
        arr[i] = output[i];
    }
}

// Driver code
int main()
{
    char arr[] = "9167621";

    countSort(arr);

    cout << "Sorted character array is " << arr;
    return 0;
}

// source : geeksforgeeks