#include<iostream>
using namespace std;

#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
private :
    float real;
    float imag;
public :
    Complex();
    Complex(float, float = 0);
    double magnitude() const;
    void print();

    //overloading the << operator
    friend ostream& operator<<(ostream&, const Complex&);

    //overloading the < and > operators
    friend bool operator>(const Complex&, const Complex&);
    friend bool operator<(const Complex&, const Complex&);
};
#endif // COMPLEX_H
