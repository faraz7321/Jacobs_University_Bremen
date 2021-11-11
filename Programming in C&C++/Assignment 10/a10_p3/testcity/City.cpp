/*
CH-230-A
City.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "City.h"

string City::getName()
{
    return name;
}

void City::setName(string newname)
{
    name = newname;
}

int City::getHabitants()
{
    return habitants;
}

void City::setHabitants(int newhabitants)
{
    habitants = newhabitants;
}

string City::getMayor()
{
    return mayor;
}

void City::setMayor(string newmayor)
{
    mayor = newmayor;
}

double City::getArea()
{
    return area;
}

void City::setArea(double newarea)
{
    area = newarea;
}

City::City(string newname, int newhabitants, string newmayor, double newarea)
{
    name = newname;
    habitants = newhabitants;
    mayor = newmayor;
    area = newarea;
}

City::City()
{
    name = "";
    habitants = 0;
    mayor = "";
    area = 0.0;
}

void City::toString()
{
    cout << "Name: " << name << endl
         << "Population: " << to_string(habitants) << endl
         << "Mayor: " << mayor << endl
         << "Area: " << to_string(area) << endl
         << endl;
}
