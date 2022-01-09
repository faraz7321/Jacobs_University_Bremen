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
#define _USE_MATH_DEFINES
#include <string>
#include <math.h>
using namespace std;

//PARENT CLASS
class Shape
{				 // base class
private:		 // private access modifier: could also be protected
	string name; // every shape will have a name
public:
	//constructors
	Shape(const string &);
	Shape();
	Shape(const Shape &); // copy constructor
	void printName() const;
	// prints the name
	// Getters and setters
	string getName() const;
	void setName(string n);
};

//CHILD CLASS
class CenteredShape : public Shape
{
	// inherits from Shape
private:
	double x, y; // the center of the shape

public:
	CenteredShape(const string &, double, double); // usual three constructors
	CenteredShape();
	CenteredShape(const CenteredShape &);
	// Getters and setters
	double getX() const;
	double getY() const;
	void setX(int X);
	void setY(int Y);
};

//CHILD CLASS
class RegularPolygon : public CenteredShape
{ // a regular polygon is a centered_shape with a number of edges
private:
	int EdgesNumber;

public:
	RegularPolygon(const string &, double, double, int);
	RegularPolygon();
	RegularPolygon(const RegularPolygon &);
	// Getters and setters
	int getEdgesNumber() const;
	void setEdgesNumber(int n);
};

//CHILD CLASS
class Rectangle : public RegularPolygon
{
	// a rectangle is a polygon with 4 edges and 2 difference lengths
private:
	double width;
	double height;

public:
	Rectangle();
	Rectangle(const string &, double, double, double, double);
	Rectangle(const Rectangle &);

	// Getters and setters
	double getWidth();
	double getHeight();
	void setWidth(double w);
	void setHeight(double h);
	//calculation
	double perimeter();
	double area();
};

//CHILD CLASS
class Square : public Rectangle
{
	// A square is a rectangle, but with only 1 length
private:
	double side;

public:
	Square();
	Square(const string &, double, double, double);
	Square(const Square &);

	// Getters and setters
	double getSide();
	void setSide(double s);

	//calculation
	double perimeter();
	double area();
};

//CHILD CLASS
class Circle : public CenteredShape
{
	// a Circle is a shape with a center and a radius
private:
	double Radius;

public:
	Circle(const string &, double, double, double);
	Circle();
	Circle(const Circle &);

	// Getters and setters
	double getRadius() const;
	void setRadius(double r);
	//calculation
	double perimeter();
	double area();
};

#endif