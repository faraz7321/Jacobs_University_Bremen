/*
CH-230-A
Vector.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "Vector.h"
#include <iostream>
#include <cmath>
using namespace std;

Vector::Vector() : size(0)
{
    arr = new double[0];
}

Vector::Vector(int newsize, double *array)
{
    size = newsize;
    arr = new double[size]; //allocating memory for array
    for (int i = 0; i < size; ++i)
    {
        arr[i] = array[i];
    }
}

Vector::Vector(const Vector &vector)
{
    size = vector.size;
    arr = new double[size]; //allocating memory for array
    for (int i = 0; i < size; ++i)
    {
        arr[i] = vector.arr[i];
    }
}

Vector::~Vector()
{
    delete[] arr;
}

void Vector::setVector(double *vector)
{
    for (int i = 0; i < size; ++i)
    {
        arr[i] = vector[i];
    }
}

int Vector::getSize()
{
    return size;
}
double *Vector::getVector()
{
    return arr;
}
void Vector::setSize(int size)
{
    size = size;
}

// MATH STUFF
double Vector::norm()
{
    double norm = 0;
    // calculate the norm
    for (int i = 0; i < size; ++i)
    {
        norm += arr[i] * arr[i];
    }
    return sqrt(norm);
}

Vector Vector::add(const Vector v) const
{
    double *new_arr = new double[size];
    for (int i = 0; i < size; ++i)
    {
        new_arr[i] = arr[i] + v.arr[i];
    }

    Vector new_vector(size, new_arr);
    delete[] new_arr; // dealocate the memory

    return new_vector;
}

Vector Vector::sub(const Vector v) const
{
    double *new_arr = new double[size];
    for (int i = 0; i < size; ++i)
    {
        new_arr[i] = arr[i] - v.arr[i];
    }

    Vector new_vector(size, new_arr);
    delete[] new_arr; // dealocate the memory

    return new_vector;
}

double Vector::scalarProd(const Vector v) const
{
    double scalar = 0;
    for (int i = 0; i < size; ++i)
    {
        scalar = scalar + (arr[i] * v.arr[i]);
    }

    return scalar;
}
void Vector::toString()
{

    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}