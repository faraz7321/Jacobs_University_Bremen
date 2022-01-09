/*
CH-230-A
Critter.cpp
Faraz Ahmad
fahmad@jacobs.university.de
*/

#include <iostream>
#include "Critter.h"

// using namespace std;

// either use namespace std or
// write the code like this
// std::string as string is part of std namespace

void Critter::setName(std::string &newname)
{
	name = newname;
}

void Critter::setHunger(int newhunger)
{
	hunger = newhunger;
}

void Critter::setBoredom(int newboredom)
{
}

void Critter::print()
{
	std::cout << "I am " << name << ". My hunger level is " << hunger << "." << std::endl;
}

int Critter::getHunger()
{
	return hunger;
}