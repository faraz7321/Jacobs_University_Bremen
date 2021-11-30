#ifndef _SQUARE_H
#define _SQUARE_H
#include "Rectangle.h"

class Square : public Rectangle
{
public:
    Square(const char *n, double a);
    ~Square();
    Square();
    double calcArea() const;
    double calcPerimeter() const;

private:
    double length;
};

#endif