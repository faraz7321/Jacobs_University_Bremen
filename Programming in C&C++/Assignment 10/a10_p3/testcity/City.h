/*
CH-230-A
City.h
Faraz Ahmad
fahmad@jacobs.university.de
*/
#pragma once
#include <string> // defines standard C++ string class
using namespace std;

class City
{
private:
	string name;
	int habitants{};
	string mayor;
	double area{};

public:
	// getter methods
	string getName();
	int getHabitants();
	string getMayor();
	double getArea();
	//setter methods
	void setName(string newname);
	void setHabitants(int newhabitants);
	void setMayor(string newmayor);
	void setArea(double newarea);
	//default constructor
	City();
	//constructor
	City(string newname, int newhabitants, string newmayor, double newarea);
	//print/service function
	void toString();
};
