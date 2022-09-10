/*
CH-231-1
problem1.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <string>
#include <complex>
using namespace std;

/**
 * @brief a template function to search
 * an element in an array of any class
 *
 * @tparam T
 * @param value
 * @param array
 * @param size
 * @return int index
 */
template <class T>
int array_search(T value, T array[], size_t size)
{
    int index = -1;
    for (int i = 0; i < size; ++i)
    {
        if (value == array[i])
        {
            index = i;
        }
    }
    return index;
}

int main()
{
    // declaring string array
    string strarr[] = {"hello", "my", "name", "is", "faraz"};
    // element to search in string array
    string name = "faraz";

    // declaring int array
    int intarr[] = {1, 6, 38, 812, 1387, 17};

    // declaring char array
    char carr[] = "hello world";

    // declaring complex class array
    complex<int> comparr[5];
    comparr[0] = complex<int>(1, 5);
    comparr[1] = complex<int>(-4, 8);
    comparr[2] = complex<int>(11, -6);
    comparr[3] = complex<int>(3, 5);
    comparr[4] = complex<int>(-1, -2);
    // element to search in complex array
    complex<int> comp(3, 5);

    // output
    cout << "string search: " << array_search(name, strarr, strarr->size()) << endl;
    cout << "int search: " << array_search(4, intarr, sizeof(intarr) / sizeof(int)) << endl;
    cout << "char search: " << array_search('w', carr, 12) << endl;
    cout << "complex search: " << array_search(comp, comparr, 5) << endl;
    return 0;
}