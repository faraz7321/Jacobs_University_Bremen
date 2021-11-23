/*
CH-230-A
Shapes.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */

// please refer to shapes.h for methods documentation

#include <iostream>
#include <cmath>
#include "Shapes.h"

Shape::Shape(const string &n) : name(n)
{
}

Shape::Shape()
{
    name = "";
}

Shape::Shape(const Shape &n)
{
    name = n.name;
}

void Shape::printName() const
{
    cout << name << endl;
}

/*
* CLASS CenteredShape methods
*/
CenteredShape::CenteredShape(const string &n, double nx, double ny) : Shape(n)
{
    x = nx;
    y = ny;
}

CenteredShape::CenteredShape()
{
    x = 0;
    y = 0;
}

CenteredShape::CenteredShape(const CenteredShape &n)
{
    x = n.x;
    y = n.y;
}

void CenteredShape::move(double nx, double ny)
{
    x = nx;
    y = ny;
}

/*
* CLASS RegularPolygon methods
*/
RegularPolygon::RegularPolygon(const string &n, double nx, double ny, int nl) : CenteredShape(n, nx, ny)
{
    EdgesNumber = nl;
}

RegularPolygon::RegularPolygon()
{
    EdgesNumber = 0;
}

RegularPolygon::RegularPolygon(const RegularPolygon &n)
{
    EdgesNumber = n.EdgesNumber;
}

Circle::Circle(const string &n, double nx, double ny, double r) : CenteredShape(n, nx, ny)
{
    Radius = r;
}

/*
* CLASS Circle methods
*/
Circle::Circle()
{
    Radius = 0;
}

Circle::Circle(const Circle &n)
{
    Radius = n.Radius;
}

/*
* CLASS Hexagon methods
*/
Hexagon::Hexagon()
{
    color = "";
    side = 0;
}
Hexagon::Hexagon(int newside, string newcolor)
{
    color = newcolor;
    side = newside;
}
Hexagon::Hexagon(const Hexagon &n)
{
    color = n.color;
    side = n.side;
}
//destructor
Hexagon::~Hexagon()
{
}
//getter and setter methods
int Hexagon::getSide()
{
    return side;
}
void Hexagon::setSide(int newside)
{
    side = newside;
}
string Hexagon::getColor()
{
    return color;
}
void Hexagon::setColor(string newcolor)
{
    color = newcolor;
}
double Hexagon::perimeter()
{
    return 6 * side;
}
double Hexagon::area()
{
    double area;
    area = ((3 * sqrt(3)) / 2) * (side * side);
    return area;
}
void Hexagon::toString()
{
    cout << "Color = " << color << endl;
    cout << "Perimeter = " << perimeter() << endl;
    cout << "Area = " << area() << endl
         << endl;
}