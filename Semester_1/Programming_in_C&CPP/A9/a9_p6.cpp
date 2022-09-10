/*
CH-230-A
a9_p6.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define MAX_SIZE 10
using namespace std;
int myfirst(int arr[]);
double myfirst(double arr[]);
char myfirst(char arr[]);
int main()
{
    int int_arr[MAX_SIZE];
    double dbl_arr[MAX_SIZE];
    char chr_arr[MAX_SIZE];

    srand(static_cast<unsigned int>(time(0)));

    // assigning random elements to array
    for (int i = 0; i < 10; i++)
    {
        int_arr[i] = -50 + (rand()) / ((RAND_MAX / (100)));
        dbl_arr[i] = -50 + (double)(rand()) / ((double)(RAND_MAX / (100)));
        chr_arr[i] = 'a' + (rand() % 26);
    }
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << int_arr[i] << " ";
    }

    cout << endl;

    cout << "Output of myfirst() called with int array: " << myfirst(int_arr) << endl;
    cout << "Output of myfirst() called with double array: " << myfirst(dbl_arr) << endl;
    cout << "Output of myfirst() called with char array: " << myfirst(chr_arr) << endl;
    return 0;
}
int myfirst(int arr[])
{
    int value;
    bool flag = false;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (arr[i] % 2 == 0 && arr[i] > 0)
        {
            value = arr[i];
            flag = true;
            break;
        }
    }
    if (flag == true)
    {
        return value;
    }
    else
    {
        return -1;
    }
}

double myfirst(double arr[])
{
    bool flag = false;
    double value;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (floor(arr[i]) == arr[i] && arr[i] < 0)
        {
            flag = true;
            value = arr[i];
            break;
        }
    }
    if (flag == true)
    {
        return value;
    }
    else
    {
        return -1.1;
    }
}
char myfirst(char arr[])
{
    bool flag = false;
    // evaluates to 1 (true) if c is a  vowel
    bool isVowel;
    char c;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        isVowel = (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u');
        if (!isVowel)
        {
            flag = true;
            c = arr[i];
            break;
        }
    }
    if (flag == true)
    {
        return c;
    }
    else
    {
        return '0';
    }
}