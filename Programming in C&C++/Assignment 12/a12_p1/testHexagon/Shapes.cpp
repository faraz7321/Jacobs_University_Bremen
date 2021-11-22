/*
CH-230-A
Shapes.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */

// please refer to shapes.h for methods documentation

#include <iostream>
#include "Shapes.h"

using namespace std;

Shape::Shape(const string &n) : name(n)
{
}

void Shape::printName() const
{
    cout << name << endl;
}

CenteredShape::CenteredShape(const string &n, double nx, double ny) : Shape(n)
{
    x = nx;
    y = ny;
}

RegularPolygon::RegularPolygon(const string &n, double nx, double ny, int nl) : CenteredShape(n, nx, ny)
{
    EdgesNumber = nl;
}

Circle::Circle(const string &n, double nx, double ny, double r) : CenteredShape(n, nx, ny)
{
    Radius = r;
}