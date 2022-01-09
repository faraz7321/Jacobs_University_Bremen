/*
CH-230-A
Critter.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <cmath>
#include "Crittter.h"

using namespace std;
//scale the value
float Critter::to_float(int newhunger)
{
    float val = 0;
    //scaling
    if (newhunger <= 10 && newhunger >= 0)
    {
        val = (float)newhunger / 10;
    }
    return val;
}
//scales back the value
int Critter::to_int(float newhunger)
{
    int val = 0;
    if (newhunger <= 1 && newhunger >= 0)
    {
        val = ((int)(newhunger * 100)) / 10;
    }
    return val;
}

//constructors
Critter::Critter()
{
    cout << "Creating object with constructor type 1" << endl;
    name = "default_critter";
    height = 5;
    boredom = 0;
    hunger = 0;
    thirst = 0;
}
Critter::Critter(string newname)
{
    cout << "Creating object with constructor type 2" << endl;
    name = newname;
    height = 5;
    boredom = 0;
    hunger = 0;
    thirst = 0;
}
Critter::Critter(string newname, int newhunger, int newboredom, double newheight)
{
    cout << "Creating object of constructor with\n"
         << "name, hunger, boredom and height as parameter " << endl;
    name = newname;
    hunger = to_float(newhunger);
    boredom = newboredom;
    height = newheight;
    thirst = hunger;
}
Critter::Critter(string newname, int newhunger, double newthirst, int newboredom, double newheight)
{
    cout << "Creating object of constructor with 5 parameters\n"
         << endl;
    name = newname;
    hunger = to_float(newhunger);
    boredom = newboredom;
    height = newheight;
    newthirst = hunger;
    thirst = newthirst;
}

void Critter::setName(string &newname)
{
    name = newname;
}

void Critter::setHunger(int newhunger)
{                                 //saves original
    hunger = to_float(newhunger); //save scaled value
}

void Critter::setBoredom(int newboredom)
{
    boredom = newboredom;
}

void Critter::print()
{
    cout << "I am " << name << ". My hunger level is " << hunger << "." << endl;
    cout << "My thirst level is " << thirst << "." << endl
         << "My height is " << height << "." << endl
         << "My boredom level is " << boredom << "." << endl
         << endl;
}

int Critter::getHunger()
{
    return to_int(hunger); //return original value
}
