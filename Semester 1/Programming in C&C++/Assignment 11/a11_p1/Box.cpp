/*
CH-230-A
Box.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "Box.h"
Box::Box()
{
    height = 0;
    width = 0;
    depth = 0;
}
Box::Box(double newheight, double newwidth, double newdepth)
{
    height = newheight;
    width = newwidth;
    depth = newdepth;
}
//copy construct
Box::Box(const Box &b1)
{
    height = b1.height;
    width = b1.width;
    depth = b1.depth;
}
//destructor
Box::~Box()
{
}
void Box::setHeight(double newheight)
{
    height = newheight;
}
double Box::getHeight()
{
    return height;
}
double Box::getWidth()
{
    return width;
}

void Box::setWidth(double newwidth)
{
    width = newwidth;
}

double Box::getDepth()
{
    return depth;
}

void Box::setDepth(double newdepth)
{
    depth = newdepth;
}
void Box::toString(int i)
{
    std::cout << "Volume of box " << i << ": " << depth * width * height << std::endl;
}