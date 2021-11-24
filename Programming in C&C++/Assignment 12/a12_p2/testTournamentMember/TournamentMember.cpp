/*
CH-230-A
TournamentMember.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "TournamentMember.h"
#include <string>
#include <cstdlib>
TournamentMember::TournamentMember()
{
    cout << "Default constructor" << endl;
    memberID = 0;
}

TournamentMember::~TournamentMember()
{
    cout << "Destructor called" << endl;
    delete[] firstName;
    delete[] lastName;
    delete[] dob;
}
TournamentMember::TournamentMember(string fn, string ln, string ndob, string ngender, string nloc)
{
    cout << "Parameterized constructor called" << endl;
    setFirstName(fn);
    setLastName(ln);
    setDob(ndob);
    memberID = rand() % 1000 + 1;
    gender = ngender;
}
string TournamentMember::getGender()
{
    return gender;
}
void TournamentMember::setGender(string newgender)
{
    gender = newgender;
}
//getter and setter methods
string TournamentMember::getName()
{
    string space = " ";
    return firstName + space + lastName;
}
string TournamentMember::getFirstName()
{
    // string fn;
    // for (int i = 0; i < 36; i++)
    // {
    //     if (firstName[i] != '\0')
    //     {
    //         fn += firstName[i];
    //     }
    // }
    //return fn;
    return firstName;
}
void TournamentMember::setFirstName(string fn)
{
    int len = fn.length();
    for (int i = 0; i < len; i++)
    {
        firstName[i] = fn[i];
    }
}
string TournamentMember::getLastName()
{
    // string fn;
    // for (int i = 0; i < 36; i++)
    // {
    //     if (lastName[i] != '\0')
    //     {
    //         fn += lastName[i];
    //     }
    // }
    // return fn;
    return lastName;
}
void TournamentMember::setLastName(string ln)
{
    int len = ln.length();
    for (int i = 0; i < len; i++)
    {
        lastName[i] = ln[i];
    }
}
string TournamentMember::getDob()
{
    return dob;
}
void TournamentMember::setDob(string ndob)
{
    for (int i = 0; i < 11; i++)
    {
        dob[i] = ndob[i];
    }
}

int TournamentMember::getMemberId()
{
    return memberID;
}

//service method
void TournamentMember::toString()
{

    cout << "Name: " << getName() << endl
         << "Date of Birth: " << dob << endl
         << "Gender: " << gender << endl
         << "Member ID: " << memberID << endl
         //<< "Team location: " << location << endl
         << endl;
}