/*
CH-230-A
testPlayer.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "TournamentMember.h"
int main()
{
    system("cls");

    //initializing data
    char fn[] = "Faraz";
    char ln[] = "Ahmad";
    char dob[] = "2001-05-07";
    //creating instances with parametrized constructor
    Player player(fn, ln, dob, 0001, "Male", 1234567, "Goal Keeper", 34, 1);

    char fn1[] = "Sarah";
    char ln1[] = "Ali";
    char dob1[] = "2006-04-18";
    Player player1(fn1, ln1, dob1, 0002, "Female", 3764817, "Attacker", 90, 0);

    char fn2[] = "Alexa";
    char ln2[] = "Amzaon";
    char dob2[] = "2004-11-05";
    Player player2(fn2, ln2, dob2, 0003, "Diverse", 2314234, "Mid Fielder", 30, 1);

    cout << endl;

    Player::setLocation("Hamburg"); //setting location

    //prinitng data
    player.toString();
    player1.toString();
    player2.incGoals(3); //increases goals of p2 from 30 to 33
    player2.toString();
    // delete tm1;
    return 0;
}
