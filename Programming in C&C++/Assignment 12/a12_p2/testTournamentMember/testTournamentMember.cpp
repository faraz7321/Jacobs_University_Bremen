/*
CH-230-A
testTournamentMember.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "TournamentMember.cpp"
int main()
{

    TournamentMember tm1("faraz", "ahmad", "2001-05-07", "male", "Pakistan");
    TournamentMember::location = "pakistan";
    tm1.toString();
    // delete tm1;
    return 0;
}
