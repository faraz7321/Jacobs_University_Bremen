/*
CH-230-A
testfraction.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "fraction.h"

int main(void)
{
    Fraction a;
    Fraction b;

    //taking input from user
    cin >> a;
    cin >> b;
    //printing greater fraction
    cout << "Greater fraction = ";
    if (a > b)
    {
        cout << a;
    }
    else if (a < b)
    {
        cout << b;
    }
    else
    {
        cout << "Both fractions are equal";
    }
    cout << endl;
    //calculating sum
    Fraction sum = a + b;
    cout << "a + b = " << sum;
    //calculating difference
    Fraction diff = a - b;
    cout << "a - b = " << diff;
    return 0;
}