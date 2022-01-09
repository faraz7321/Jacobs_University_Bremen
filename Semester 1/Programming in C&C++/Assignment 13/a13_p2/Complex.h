/*
CH-230-A
Complex.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <string>
using namespace std;
class Complex
{
private:
	double real, imag;

public:
	// default constructor
	Complex();
	// constructors
	Complex(double r, double i);
	Complex(Complex &obj);
	// destructor
	~Complex();
	// operator overloading
	friend ostream &operator<<(ostream &, const Complex &);
	friend istream &operator>>(istream &, Complex &);
	friend Complex operator*(Complex, Complex);
	friend Complex operator+(const Complex &, const Complex &);
	friend Complex operator-(const Complex &, const Complex &);
	bool operator=(const Complex &);
	// operation methods
	Complex conjugate(Complex c);
	// getter methods
	double getReal();
	double getImag();
	// setter methods
	void setReal(double re);
	void setImag(double im);
};
