/*
CH-230-A
TournamentMember.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "TournamentMember.h"
#include <string>
#include <cstdlib>

//initializing static variable
string TournamentMember::location = "Pakistan";

/**
 * @brief Construct a new Tournament Member:: Tournament Member object
 * 
 */
TournamentMember::TournamentMember()
{
    cout << "Default constructor" << endl;
    memberID = 0;
}
/**
 * @brief Construct a new Tournament Member:: Tournament Member object
 * 
 * @param tm 
 */
TournamentMember::TournamentMember(TournamentMember &tm)
{
    cout << "Copy constructor called" << endl;
    firstName = tm.firstName;
    lastName = tm.lastName;
    dob = tm.dob;
    memberID = tm.memberID;
    gender = tm.gender;
}
/**
 * @brief Destroy the Tournament Member:: Tournament Member object
 * 
 */
TournamentMember::~TournamentMember()
{
    cout << "Destructor called" << endl;
    delete firstName;
    delete lastName;
    delete dob;
}
/**
 * @brief Construct a new Tournament Member:: Tournament Member object
 * 
 * @param fn 
 * @param ln 
 * @param ndob 
 * @param ngender 
 */
TournamentMember::TournamentMember(char *fn, char *ln, char *ndob, string ngender)
{
    cout << "Parameterized constructor called" << endl;
    firstName = fn;
    lastName = ln;
    dob = ndob;
    memberID = rand() % 1000 + 1;
    gender = ngender;
}
//service method
void TournamentMember::toString()
{
    cout << "Name: " << firstName << " " << lastName << endl
         << "Date of Birth: " << dob << endl
         << "Gender: " << gender << endl
         << "Member ID: " << memberID << endl
         << "Team location: " << location << endl
         << endl;
}