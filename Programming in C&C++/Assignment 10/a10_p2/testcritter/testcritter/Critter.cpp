/*
CH-230-A
Critter.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "Critter.h"
using namespace std;

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

void Critter::setGrade(char newgrade)
{
	grade = newgrade;
}

void Critter::setMarks(int newmarks)
{
	marks = newmarks;
}
char Critter::getGrade()
{
	return grade;
}

int Critter::getMarks()
{
	return marks;
}

void Critter::print()
{
	cout << "I am " << name << ". My hunger level is " << hunger << "." << endl;
	cout << "My final grade is " << grade << " and " << marks << " marks." << endl;
}

int Critter::getHunger()
{
	return hunger;
}