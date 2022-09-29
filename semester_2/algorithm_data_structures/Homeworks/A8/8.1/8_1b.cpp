#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief implementaion of bucketsort
 *
 * @param arr
 * @param n
 */
void bucketSort(float arr[], int n)
{

    // Create n empty buckets
    vector<float> bucket[n];

    int index_b = 0;
    /*Put array elements
    in different buckets*/
    for (int i = 0; i < n; i++)
    {
        int index_b = n * arr[i]; // Index in bucket
        bucket[index_b].push_back(arr[i]);
    }

    // Sort individual buckets
    for (int i = 0; i < n; i++)
    {
        sort(bucket[i].begin(), bucket[i].end());
    }

    // Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < bucket[i].size(); j++)
        {
            arr[index++] = bucket[i][j];
        }
    }
}

/**
 * @brief driver
 *
 * @return int
 */
int main()
{
    float arr[] = {0.9, 0.1, 0.6, 0.7, 0.6, 0.3, 0.1};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);

    cout << "Sorted array is \n";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
// source : geeksforgeeks