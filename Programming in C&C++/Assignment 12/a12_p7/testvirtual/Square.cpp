#include <iostream>
#include "Square.h"
Square::Square(const char *n, double a)
    : Rectangle(n, a, a) {}

Square::~Square()
{
}

Square::Square()
{
}

double Square::calcArea() const
{
    std::cout << "calcArea of Square...";
    return Rectangle::calcArea();
}
double Square::calcPerimeter() const
{
    std::cout << "calcPerimeter of Square...";
    return (Rectangle::calcPerimeter());
}