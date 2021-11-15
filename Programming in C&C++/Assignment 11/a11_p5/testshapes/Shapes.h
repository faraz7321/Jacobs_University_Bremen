/*
CH-230-A
Shapes.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
/* 
	Classic shape examples: an inheritance tree in a geometric context
*/
#ifndef __SHAPES_H
#define __SHAPES_H
#include <string>

/**
 * @brief PARENT/BASE CLASS
 * 
 */
class Shape
{                     // base class
private:              // private access modifier: could also be protected
    std::string name; // every shape will have a name
public:
    Shape(const std::string &); // builds a shape with a name
    Shape();                    // empty shape
    Shape(const Shape &);       // copy constructor
    void printName() const;     // prints the name
};

/**
 * @brief inherits from Shape
 * 
 */
class CenteredShape : public Shape
{
private:
    double x{}, y{}; // the center of the shape
public:
    CenteredShape(const std::string &, double, double); // usual three constructors
    CenteredShape();
    CenteredShape(const CenteredShape &);
    void move(double, double); // moves the shape, i.e. it modifies it center
};

/**
 * @brief a Circle is a shape with a center and a radius
 * 
 */
class Circle : public CenteredShape
{
private:
    double Radius{};

public:
    Circle(const std::string &, double, double, double);
    Circle();
    Circle(const Circle &);
};

/**
 * @brief a regular polygon is a centered_shape with a number of edge
 * 
 */
class RegularPolygon : public CenteredShape
{
private:
    int EdgesNumber{};

public:
    RegularPolygon(const std::string &, double, double, int);
    RegularPolygon();
    RegularPolygon(const RegularPolygon &);
};

/**
 * @brief Rectangle is a regular_polygon
 * 
 */
class Rectangle : public RegularPolygon
{
private:
    /* data */
public:
    Rectangle();
    ~Rectangle();
};

/**
 * @brief square is a regular_polygon
 * 
 */
class Square : public RegularPolygon
{
private:
    /* data */
public:
    Square();
    ~Square();
};

#endif
