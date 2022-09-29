/*
CH-230-A
Complex.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <string>
#include "Complex.h"
using namespace std;
Complex::Complex()
{
	real = 0;
	imag = 0;
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
 * @brief adds 2 complex numbers
 * 
 * @param c 
 * @return Complex 
 */
Complex Complex::add(Complex c)
{
	Complex add;
	add.real = real + c.real;
	add.imag = imag + c.imag;
	return add;
}
/**
 * @brief subtracts 2 complex numbers
 * 
 * @param c 
 * @return Complex 
 */
Complex Complex::sub(Complex c)
{
	Complex Sub;
	Sub.real = real - c.real;
	Sub.imag = imag - c.imag;
	return Sub;
}
/**
 * @brief multiply 2 complex numbers
 * 
 * @param c 
 * @return Complex 
 */
Complex Complex::mult(Complex c)
{
	Complex mult;
	mult.real = (real * c.real) - (imag * c.imag);
	mult.imag = (real * c.imag) + (c.real * imag);
	return mult;
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

void Complex::toString()
{
	if (imag >= 0)
	{
		cout << "(" << real << " +" << imag << "i"
			 << ")";
	}
	else
	{
		cout << "(" << real << " " << imag << "i"
			 << ")";
	}
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
