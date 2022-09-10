/*
CH-230-A
Box.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#pragma once
class Box
{
private:
    double height{};
    double width{};
    double depth{};

public:
    //constructors
    Box();
    Box(const Box &b1);
    Box(double height, double width, double depth);
    //destructor
    ~Box();
    //getter and setters
    void setHeight(double height);
    void setDepth(double depth);
    void setWidth(double width);
    double getDepth();
    double getHeight();
    double getWidth();
    //service method
    void toString(int i);
};