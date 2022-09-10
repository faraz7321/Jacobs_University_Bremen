/*
CH-230-A
testvector.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "Vector.h"
#include <iostream>
using namespace std;
int main()
{
    //creating 4 instances of vectors
    Vector v1; //without parameter
    double values[3] = {1, 2, 3};
    Vector v2(3, values); //with 2 parameters
    Vector v3(v2);        //copy constructor
    double values2[3] = {3, 2, 1};
    Vector v4(3, values2); //with parameter

    // calculating norm of second vector
    cout << "norm of 2nd vector =  " << v2.norm() << endl;

    //calculating sum of vector2 & vector4
    cout << "vector2 + vector4 =  ";
    v2.add(v4).toString();

    //calculating diff of vector2 & vector4
    cout << "vector2 - vector4 = ";
    v2.sub(v4).toString();

    //calculating diff of vector2 & vector4
    cout << "scalar product of vector2 * vector4 = ";
    cout << v2.scalarProd(v4);

    cout << endl;

    return 0;
}