/*
CH-230-A
Critter.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "Critter.h"
using namespace std;

Critter::Critter()
{
	cout << "Creating object with constructor type 1" << endl;
	name = "default_critter";
	height = 5;
	boredom = 0;
	hunger = 0;
}
Critter::Critter(string newname)
{
	cout << "Creating object with constructor type 2" << endl;
	name = newname;
	height = 5;
	boredom = 0;
	hunger = 0;
}
Critter::Critter(string newname, int newhunger, int newboredom, double newheight)
{
	cout << "Creating object of constructor with\n"
		 << "name, hunger, boredom and height as parameter " << endl;
	name = newname;
	hunger = newhunger;
	boredom = newboredom;
	height = newheight;
}

void Critter::setName(string &newname)
{
	name = newname;
}

void Critter::setHunger(int newhunger)
{
	hunger = newhunger;
}

void Critter::setBoredom(int newboredom)
{
	boredom = newboredom;
}

void Critter::print()
{
	cout << "I am " << name << "." << endl
		 << "My hunger level is " << hunger << "." << endl
		 << "My height is " << height << "." << endl
		 << "My boredom level is " << boredom << "." << endl
		 << endl;
}

int Critter::getHunger()
{
	return hunger;
}