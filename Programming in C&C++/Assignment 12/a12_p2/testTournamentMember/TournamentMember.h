/*
CH-230-A
TournamentMember.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#pragma once
#include <iostream>
using namespace std;
class TournamentMember
{
private:
	char *firstName = new char[36];
	char *lastName = new char[36];
	char *dob = new char[11];
	int memberID;
	string gender;

public:
	static string location;
	TournamentMember();
	TournamentMember(string fn, string ln, string dob, string gender, string nloc);
	~TournamentMember();
	//getter and setter methods
	string getName();
	string getFirstName();
	void setFirstName(string fn);
	string getLastName();
	void setLastName(string ln);
	string getDob();
	void setDob(string ndob);
	int getMemberId();
	void setGender(string newgender);
	//service method
	void toString();
	string getGender();
};