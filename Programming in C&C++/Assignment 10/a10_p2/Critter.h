/*
CH-230-A
Critter.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#pragma once
#include <string> // defines standard C++ string class

/* First C++ class */
class Critter
{
private: // data members are private
    std::string name;
    int hunger;
    int boredom;
    double height;
    char grade;
    int marks;

public: // business logic methods are public
    // setter methods
    void setName(std::string &newname);
    void setHunger(int newhunger);
    void setBoredom(int newboredom);
    void setGrade(char newgrade);
    void setMarks(int newmarks);
    // getter method
    int getHunger();
    int getMarks();
    char getGrade();
    // service method
    void print();
};