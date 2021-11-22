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

// Constructors
Shape::Shape()
{
    name = "";
}

Shape::Shape(const string &n)
{
    name = n;
}

Shape::Shape(const Shape &shape)
{
    name = shape.name;
}

void Shape::printName() const
{
    cout << name << endl;
}

string Shape::getName() const
{
    return name;
}

void Shape::setName(string n)
{
    name = n;
}

/*
    ///////////////////CenterdShape section///////////////////
*/
// Constructors
CenteredShape::CenteredShape() : Shape()
{
    x = 0;
    y = 0;
}

CenteredShape::CenteredShape(const string &n, double newx, double newy) : Shape(n)
{
    x = newx;
    y = newy;
}

CenteredShape::CenteredShape(const CenteredShape &shape) : Shape(shape)
{
    x = shape.x;
    y = shape.y;
}

double CenteredShape::getX() const
{
    return x;
}
double CenteredShape::getY() const
{
    return y;
}
void CenteredShape::setX(int X)
{
    x = X;
}
void CenteredShape::setY(int Y)
{
    y = Y;
}
/*
    ///////////////////RegularPolygon section/////////////////////////
*/

// Constructors
RegularPolygon::RegularPolygon() : CenteredShape()
{
    EdgesNumber = 0;
}

RegularPolygon::RegularPolygon(const string &n, double newx, double newy, int newl) : CenteredShape(n, newx, newy)
{

    EdgesNumber = newl;
}

RegularPolygon::RegularPolygon(const RegularPolygon &shape) : CenteredShape(shape)
{
    EdgesNumber = shape.EdgesNumber;
}
int RegularPolygon::getEdgesNumber() const
{
    return EdgesNumber;
}
void RegularPolygon::setEdgesNumber(int n)
{
    EdgesNumber = n;
}

/*
    ///////////////////Rectangle section///////////////////
*/
// Constructors
Rectangle::Rectangle() : RegularPolygon()
{
    width = 0;
    height = 0;
    setEdgesNumber(4);
}

Rectangle::Rectangle(const string &n, double newx, double newy,
                     double newwidth, double newheight) : RegularPolygon(n, newx, newy, 4)
{
    width = newwidth;
    height = newheight;
}

Rectangle::Rectangle(const Rectangle &shape) : RegularPolygon(shape)
{
    width = shape.width;
    height = shape.height;
}
// Getters and setters
double Rectangle::getWidth()
{
    return width;
}
double Rectangle::getHeight()
{
    return height;
}
void Rectangle::setWidth(double w)
{
    width = w;
}
void Rectangle::setHeight(double h)
{
    height = h;
}

double Rectangle::perimeter()
{
    return (width + height) * 2;
}
double Rectangle::area()
{
    return width * height;
}

/*
    ///////////////////Square section///////////////////
*/
// Constructors
Square::Square() : Rectangle()
{
    side = 0;
}

Square::Square(const string &n, double newx, double newy, double newside) : Rectangle(n, newx, newy, newside, newside)
{
    side = newside;
}

Square::Square(const Square &shape) : Rectangle(shape.getName(), shape.getX(), shape.getY(),
                                                shape.side, shape.side)
{
    side = shape.side;
}
// Getters and setters
double Square::getSide()
{
    return side;
}
void Square::setSide(double s)
{
    side = s;
}

double Square::perimeter()
{
    return side * 4;
}
double Square::area()
{
    return side * side;
}

/*
    ///////////////////Circle section///////////////////
*/
// Constructors
Circle::Circle() : CenteredShape()
{
    Radius = 0;
}

Circle::Circle(const string &n, double newx, double newy, double r) : CenteredShape(n, newx, newy)
{
    Radius = r;
}

Circle::Circle(const Circle &shape) : CenteredShape(shape)
{
    Radius = shape.Radius;
}
// Getters and setters
double Circle::getRadius() const
{
    return Radius;
}
void Circle::setRadius(double r)
{
    Radius = r;
}

double Circle::perimeter()
{
    double perimeter = Radius * Radius * M_PI;
    return perimeter;
}
double Circle::area()
{
    double area = 2 * M_PI * Radius;
    return area;
}
