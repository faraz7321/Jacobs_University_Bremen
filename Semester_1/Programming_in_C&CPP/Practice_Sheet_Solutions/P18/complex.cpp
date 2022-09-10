#include<iostream>
#include<math.h>
#include "complex.h"
using namespace std;

Complex :: Complex (float a, float b)
{
    real = a;
    imag = b;
}

double Complex :: magnitude() const
{
    return sqrt(real*real + imag*imag);
}

void Complex :: print()
{
    if (imag)
        cout << noshowpos << real << showpos << imag << "i" << endl;
    else
        cout << noshowpos << real << endl;
}

ostream& operator<<(ostream& out, const Complex& z)
{
    if (z.imag)
        out << noshowpos << z.real << showpos << z.imag << "i" << endl;
    else
        cout << noshowpos << z.real << endl;
}

bool operator >(const Complex& z1, const Complex& z2)
{
    return z1.magnitude() > z2.magnitude();
}

bool operator <(const Complex& z1, const Complex& z2)
{
    return z1.magnitude() < z2.magnitude();
}
