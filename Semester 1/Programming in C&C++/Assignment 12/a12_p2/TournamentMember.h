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
	static string location;

public:
	TournamentMember();
	TournamentMember(TournamentMember &);
	TournamentMember(char *fn, char *ln, char *dob, string ngender);
	~TournamentMember();
	//inline getter and setter methods
	inline string getFirstName() const { return firstName; }
	inline void setFirstName(char *fn) { firstName = fn; }
	inline string getLastName() const { return lastName; }
	inline void setLastName(char *ln) { lastName = ln; }
	inline string getDob() const { return dob; }
	inline void setDob(char *ndob) { dob = ndob; }
	inline int getMemberId() const { return memberID; }
	inline void setGender(string newgender) { gender = newgender; }
	inline static void setLocation(string loc) { location = loc; }
	//service method
	void toString();
	string getGender();
};
