/*
CH-230-A
a9_p7.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
using namespace std;
void swapping(int &a, int &b);                       // swap ints
void swapping(float &a, float &b);                   // swap floats
void swapping(const char *&str1, const char *&str2); // swap char pointers

int main()
{
    int a = 7, b = 15;
    float x = 3.5f, y = 9.2f;
    const char *str1 = "One";
    const char *str2 = "Two";
    cout << "a=" << a << ", b=" << b << endl;
    cout << "x=" << x << ", y=" << y << endl;
    cout << "str1=" << str1 << ", str2=" << str2 << endl;
    swapping(a, b);
    swapping(x, y);
    swapping(str1, str2);
    cout << "a=" << a << ", b=" << b << endl;
    cout << "x=" << x << ", y=" << y << endl;
    cout << "str1=" << str1 << ", str2=" << str2 << endl;
    return 0;
}

void swapping(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void swapping(float &a, float &b)
{
    float temp = a;
    a = b;
    b = temp;
}
void swapping(const char *&str1, const char *&str2)
{
    const char *pSwap = str1;
    str1 = str2;
    str2 = pSwap;
}