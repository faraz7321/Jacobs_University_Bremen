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
	char firstName[36];
	char lastName[36];
	char dob[11];
	int memberID;
	enum gender
	{
		MALE,
		FEMALE,
		DIVERSE
	};

public:
	static string location;
	TournamentMember();
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
	//service method
	string toString();
	string getStringFromEnum(gender e);
};