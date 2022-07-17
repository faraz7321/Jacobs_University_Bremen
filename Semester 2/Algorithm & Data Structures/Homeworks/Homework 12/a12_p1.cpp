#include <iostream>
#include <algorithm>
#include <vector>
#define MAX(x, y) ((x > y) ? x : y)
using namespace std;
int main()
{

    int arr[] = {8, 3, 6, 50, 10, 8, 100, 30, 60, 40, 80};
    int n = sizeof(arr) / sizeof(int);
    int *new_arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        new_arr[i] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (arr[i] > arr[j])
            {
                new_arr[i] = MAX(new_arr[i], new_arr[j] + 1);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << new_arr[i] << " ";
    }

    int counter = *max_element(new_arr, new_arr + n);

    vector<int> result;
    for (int i = n - 1; i >= -1; i--)
    {
        if (counter == new_arr[i])
        {
            counter -= 1;
            result.push_back(arr[i]);
        }
        if (counter == 0)
            break;
    }
    cout << endl;
    reverse(result.begin(), result.end());
    for (auto i = result.begin(); i != result.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    return 0;
}