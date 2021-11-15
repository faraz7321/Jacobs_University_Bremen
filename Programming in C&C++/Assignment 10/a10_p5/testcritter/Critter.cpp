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
}

int Critter::getHunger()
{
    return to_int(hunger); //return original value
}
