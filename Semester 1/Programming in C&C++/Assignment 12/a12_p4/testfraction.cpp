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
    Fraction c(5);

    //a.print();
    //b.print();
    //c.print();
    //taking input from user
    cin >> a;
    cin >> b;
    //printing fractions
    cout << "a = " << a;
    cout << "b = " << b;
    cout << "c = " << c;
    Fraction d = a / b; // a divided by b
    cout << "a / b = " << d;
    d = b * c; // b multiply with c
    cout << "a x c = " << d;
    return 0;
}