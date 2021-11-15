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

Shape::Shape()
{
}

Shape::Shape(const Shape &)
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

CenteredShape::CenteredShape()
{
}

CenteredShape::CenteredShape(const CenteredShape &)
{
}

void CenteredShape::move(double, double)
{
}

RegularPolygon::RegularPolygon(const string &n, double nx, double ny, int nl) : CenteredShape(n, nx, ny)
{
    EdgesNumber = nl;
}

RegularPolygon::RegularPolygon()
{
}

RegularPolygon::RegularPolygon(const RegularPolygon &)
{
}

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}
Square::Square()
{
}

Square::~Square()
{
}

Circle::Circle(const string &n, double nx, double ny, double r) : CenteredShape(n, nx, ny)
{
    Radius = r;
}

Circle::Circle()
{
}

Circle::Circle(const Circle &)
{
}
