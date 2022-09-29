/*
CH-230-A
Complex.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#pragma once
class Complex
{
private:
	double real, imag;

public:
	//default constructor
	Complex();
	//constructors
	Complex(double r, double i);
	Complex(Complex &obj);
	//destructor
	~Complex();
	//operation methods
	Complex add(Complex c);
	Complex sub(Complex c);
	Complex mult(Complex c);
	Complex conjugate(Complex c);
	//getter methods
	double getReal();
	double getImag();
	//setter methods
	void setReal(double re);
	void setImag(double im);
	//service method
	void toString();
};
