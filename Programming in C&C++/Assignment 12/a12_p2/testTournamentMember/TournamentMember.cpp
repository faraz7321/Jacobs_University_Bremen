/*
CH-230-A
TournamentMember.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "TournamentMember.h"
#include <string>
TournamentMember::TournamentMember()
{
}

TournamentMember::~TournamentMember()
{
}
string TournamentMember::getStringFromEnum(gender e)
{
    switch (e)
    {

    case MALE:
        return "Male";
    case FEMALE:
        return "Female";
    case DIVERSE:
        return "Diverse";
    default:
        cout << "Bad MyEnum";
    }
}
//getter and setter methods
string TournamentMember::getName()
{
    string space = " ";
    return firstName + space + lastName;
}
string TournamentMember::getFirstName()
{
    return firstName;
}
void TournamentMember::setFirstName(string fn)
{
    if (fn.length() <= 36)
    {
        for (int i = 0; i < fn.length(); i++)
        {
            firstName[i] = fn[i];
        }
    }
}
string TournamentMember::getLastName()
{
    return lastName;
}
void TournamentMember::setLastName(string ln)
{
    if (ln.length() <= 36)
    {
        for (int i = 0; i < ln.length(); i++)
        {
            lastName[i] = ln[i];
        }
    }
}
string TournamentMember::getDob()
{
    return dob;
}
void TournamentMember::setDob(string ndob)
{
    if (ndob.length() <= 36)
    {
        for (int i = 0; i < ndob.length(); i++)
        {
            dob[i] = ndob[i];
        }
    }
}
int TournamentMember::getMemberId()
{
}
//service method
string TournamentMember::toString()
{
}