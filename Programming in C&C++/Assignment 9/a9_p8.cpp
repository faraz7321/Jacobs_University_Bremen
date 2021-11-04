/*
CH-230-A
a9_p8.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
void subtract_max(int *a, int size);
void deallocate(int *a);
void print(int *a, int size);
bool comp(int a, int b)
{
    return (a < b);
}
int main()
{
    int n;

    cin >> n;

    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << "Elements in array before subtracting max: ";
    print(a, n);

    subtract_max(a, n);
    cout << "\nElements in array after subtracting max: ";
    print(a, n);

    deallocate(a);
    cout << "\n";

    return 0;
}
void subtract_max(int *a, int size)
{
    int max = a[0];
    for (int i = 0; i < size; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
        }
    }
    for (int i = 0; i < size; i++)
    {
        a[i] = a[i] - max;
    }
}

void print(int *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
    }
}
void deallocate(int *a)
{
    delete[] a;
}