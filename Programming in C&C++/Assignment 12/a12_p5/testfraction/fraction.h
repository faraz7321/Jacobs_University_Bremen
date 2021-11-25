/*
CH-230-A
fraction.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
using namespace std;

// simple class for fractions

#ifndef FRACTION_H_
#define FRACTION_H_

class Fraction
{

private:     // internal implementation is hidden
    int num; // numerator
    int den; // denominator

    static int gcd(int a, int b); // calculates the gcd of a and b
    static int lcm(int a, int b);

public:
    Fraction();             // empty constructor
    Fraction(int, int = 1); // constructor taking values for fractions and
                            // integers. Denominator by default is 1
    void print();           // prints it to the screen
    //operator overloading
    friend ostream &operator<<(ostream &out, const Fraction &f);
    friend Fraction operator*(Fraction f1, Fraction f2);
    friend Fraction operator/(Fraction f1, Fraction f2);
    friend istream &operator>>(istream &in, Fraction &f);
    friend Fraction operator+(const Fraction &f1, const Fraction &f2);
    friend Fraction operator-(const Fraction &f1, const Fraction &f2);
    bool operator>(const Fraction &f);
    bool operator<(const Fraction &f);
    Fraction &operator=(const Fraction &f1);
};

#endif /* FRACTION_H_ */
