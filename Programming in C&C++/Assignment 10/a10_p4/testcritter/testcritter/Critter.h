/*
CH-230-A
Critter.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#pragma once
#include <string> // defines standard C++ string class
using namespace std;

class Critter
{
private: // data members are private
    string name;
    int hunger;
    int boredom;
    double height;

public: // business logic methods are public
    Critter();
    Critter(string newname);
    Critter(string name, int newhunger, int newboredom, double newheight);
    // setter methods
    void setName(string &newname);
    void setHunger(int newhunger);
    void setBoredom(int newboredom);
    // getter method
    int getHunger();
    // service method
    void print();
};