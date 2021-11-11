/*
CH-230-A
testcomplex.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "Complex.h"
using namespace std;
int main()
{
    Complex c1(-7, 4);
    Complex c2(-3, -8);
    Complex c3;
    cout << "First complex number: ";
    c1.toString();
    cout << "\nSecond complex number: ";
    c2.toString();
    cout << "\nConjugate of first complex number: ";
    Complex c1_conj;
    c1_conj = c1_conj.conjugate(c1);
    c1_conj.toString();

    c3 = c1.add(c2);
    cout << "\n\nSum: \n";
    c1.toString();
    cout << " + ";
    c2.toString();
    cout << " = ";
    c3.toString();

    c3 = c2.sub(c1);
    cout << "\n\nDiffernce: \n";
    c2.toString();
    cout << " - ";
    c1.toString();
    cout << " = ";
    c3.toString();

    c3 = c1.mult(c2);
    cout << "\n\nMultiplication: \n";
    c1.toString();
    cout << " x ";
    c2.toString();
    cout << " = ";
    c3.toString();
    cout << endl;

    return 0;
}
