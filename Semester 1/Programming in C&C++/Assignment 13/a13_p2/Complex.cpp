/*
CH-230-A
Complex.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "Complex.h"
Complex::Complex()
{
	real = 0.0;
	imag = 0.0;
}

Complex::Complex(double r, double i)
{
	real = r;
	imag = i;
}

Complex::Complex(Complex &obj)
{
	real = obj.real;
	imag = obj.imag;
}
// Define the destructor.
Complex::~Complex()
{
}

/**
 * @brief finds conjugate on a complex number
 *
 * @param c
 * @return Complex
 */
Complex Complex::conjugate(Complex c)
{
	Complex con;
	con.real = c.real;
	con.imag = -1 * c.imag;
	return con;
}

double Complex::getReal()
{
	return real;
}

double Complex::getImag()
{
	return imag;
}

void Complex::setReal(double re)
{
	real = re;
}

void Complex::setImag(double im)
{
	imag = im;
}
// operator overloading
/**
 * @brief << operator overloaded
 *
 * @param out
 * @param f
 * @return ostream&
 */
ostream &operator<<(ostream &out, const Complex &c)
{
	if (c.imag >= 0)
	{
		out << "(" << c.real << " + " << c.imag << "i"
			<< ")";
	}
	else
	{
		out << "(" << c.real << " " << c.imag << "i"
			<< ")";
	}

	return out;
}
/**
 * @brief >> operator overloaded
 *
 * @param in
 * @param f
 * @return istream&
 */
istream &operator>>(istream &in, Complex &c)
{
	cout << "Enter the real part: ";
	cin >> c.real;
	cout << "Enter the imaginary part: ";
	cin >> c.imag;

	return in;
}
/**
 * @brief multiplication
 *
 * @param f1
 * @param f2
 * @return Complex
 */
Complex operator*(Complex c1, Complex c2)
{
	double r = (c1.real * c2.real) - (c1.imag * c2.imag);
	double i = (c1.real * c2.imag) + (c2.real * c1.imag);
	Complex mult(r, i);
	return mult;
}
/**
 * @brief addition
 *
 * @param f1
 * @param f2
 * @return Complex
 */
Complex operator+(const Complex &c1, const Complex &c2)
{
	double r = c1.real + c2.real;
	double i = c1.imag + c2.imag;
	Complex add(r, i);
	return add;
}
/**
 * @brief subtraction
 *
 * @param f1
 * @param f2
 * @return Complex
 */
Complex operator-(const Complex &c1, const Complex &c2)
{
	double r = c1.real - c2.real;
	double i = c1.imag - c2.imag;
	Complex sub(r, i);
	return sub;
}
/**
 * @brief equal = operator overloaded
 *
 * @param f1
 * @return true
 * @return false
 */
bool Complex::operator=(const Complex &c1)
{
	bool flag = false;
	real = c1.real;
	imag = c1.imag;
	flag = true;
	return flag;
}