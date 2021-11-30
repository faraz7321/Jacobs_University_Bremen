/*
CH-230-A
fraction.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <sstream>
#include <cmath>
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
    //int tmp_gcd = 1;

    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;

    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, fmod(a, b));
    }
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
    if (a % 2 == 0 && b % 2 == 0)
    {
        return a * b;
    }
    else
    {
        return a * b / gcd(a, b);
    }
}
/**
 * @brief 
 * 
 */
void Fraction::print()
{
    std::cout << num << "/" << den << std::endl;
}
//operator overloading
/**
 * @brief << operator overloaded
 * 
 * @param out 
 * @param f 
 * @return ostream& 
 */
ostream &operator<<(ostream &out, const Fraction &f)
{
    out << f.num << "/" << f.den << endl;

    return out;
}
/**
 * @brief >> operator overloaded
 * 
 * @param in 
 * @param f 
 * @return istream& 
 */
istream &operator>>(istream &in, Fraction &f)
{
    cout << "Enter the numerator: ";
    cin >> f.num;
    cout << "Enter the denominator: ";
    cin >> f.den;

    return in;
}
/**
 * @brief multiplication
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator*(Fraction f1, Fraction f2)
{
    int n = f1.num * f2.num;
    int d = f1.den * f2.den;

    return Fraction(n, d);
}
/**
 * @brief division
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator/(Fraction f1, Fraction f2)
{
    int n = f1.num * f2.den;
    int d = f1.den * f2.num;

    return Fraction(n, d);
}
/**
 * @brief addition
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator+(const Fraction &f1, const Fraction &f2)
{
    int n = f1.num * f2.den + f2.num * f1.den;
    int d = Fraction::lcm(f1.den, f2.den);

    return Fraction(n, d);
}
/**
 * @brief subtraction
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator-(const Fraction &f1, const Fraction &f2)
{
    int n = f1.num * f2.den - f2.num * f1.den;
    int d = Fraction::lcm(f1.den, f2.den);

    return Fraction(n, d);
}
/**
 * @brief greater or less than operator
 * overloading
 * 
 * @param f 
 * @return true 
 * @return false 
 */
bool Fraction::operator>(const Fraction &f)
{
    bool flag;
    float n1 = (float)num / den, n2 = (float)f.num / f.den;
    //cout << n1 << " " << n2;
    if (n1 > n2)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }

    return flag;
}
/**
 * @brief greater or less than operator
 * overloading
 * 
 * @param f 
 * @return true 
 * @return false 
 */
bool Fraction::operator<(const Fraction &f)
{
    bool flag = false;
    float n1 = (float)num / den, n2 = (float)f.num / f.den;
    if (n1 < n2)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }

    return flag;
}
/**
 * @brief equal = operator overloaded
 * 
 * @param f1 
 * @return true 
 * @return false 
 */
bool Fraction::operator=(const Fraction &f1)
{
    bool flag = false;
    num = f1.num;
    den = f1.den;
    flag = true;
    return flag;
}
