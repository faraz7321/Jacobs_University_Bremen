/*
CH-230-A
fraction.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <sstream>
#include "fraction.h"

/**
 * @brief Construct a new Fraction object
 * 
 */
Fraction::Fraction()
{
    num = 1;
    den = 1;
}
/**
 * @brief Construct a new Fraction object
 * 
 * @param n 
 * @param d 
 */
Fraction::Fraction(int n, int d)
{
    int tmp_gcd = gcd(n, d);

    num = n / tmp_gcd;
    den = d / tmp_gcd;
}
/**
 * @brief calculates greatest common factor
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int Fraction::gcd(int a, int b)
{
    int tmp_gcd = 1;

    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;

    while (a > 0)
    {
        if (a < b)
        {
            int t = a; // swap u and v
            a = b;
            b = t;
        }

        a -= b;
    }

    tmp_gcd = b;

    return tmp_gcd;
}

/**
 * @brief calculates lcm
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int Fraction::lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

void Fraction::print()
{
    std::cout << num << "/" << den << std::endl;
}
//operator overloading
ostream &operator<<(ostream &out, const Fraction &f)
{
    out << f.num << "/" << f.den << endl;

    return out;
}
istream &operator>>(istream &in, Fraction &f)
{
    cout << "Enter the numerator: ";
    cin >> f.num;
    cout << "Enter the denominator: ";
    cin >> f.den;

    return in;
}
Fraction operator*(Fraction f1, Fraction f2)
{
    int n = f1.num * f2.num;
    int d = f1.den * f2.den;

    return Fraction(n, d);
}

Fraction operator/(Fraction f1, Fraction f2)
{
    int n = f1.num * f2.den;
    int d = f1.den * f2.num;

    return Fraction(n, d);
}