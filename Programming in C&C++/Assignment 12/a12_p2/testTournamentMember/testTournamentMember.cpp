/*
CH-230-A
testTournamentMember.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "TournamentMember.h"
int main()
{
    //initializing data
    char fn[] = "Faraz";
    char ln[] = "Ahmad";
    char dob[] = "2001-05-07";
    //creating instance with parametrized constructor
    TournamentMember tm1(fn, ln, dob, "Male");
    TournamentMember::setLocation("Pakistan"); //setting location
    //prinitng data
    tm1.toString();
    // delete tm1;
    return 0;
}
