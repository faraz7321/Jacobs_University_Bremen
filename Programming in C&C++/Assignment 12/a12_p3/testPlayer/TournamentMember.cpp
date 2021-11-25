/*
CH-230-A
TournamentMember.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "TournamentMember.h"
#include <string>

//initializing static variable
string TournamentMember::location = "Pakistan";

//PARENT CLASS METHODS//

/**
 * @brief Construct a new Tournament Member object
 * 
 */
TournamentMember::TournamentMember()
{
    cout << "TournamentMember Default constructor" << endl;
}
/**
 * @brief Construct a new Tournament Member object
 * 
 * @param tm 
 */
TournamentMember::TournamentMember(TournamentMember &tm)
{
    cout << "TournamentMember Copy constructor called" << endl;
    firstName = tm.firstName;
    lastName = tm.lastName;
    dob = tm.dob;
    memberID = tm.memberID;
    gender = tm.gender;
}
/**
 * @brief Destroy the Tournament Member object
 * 
 */
TournamentMember::~TournamentMember()
{
    cout << "TournamentMember Destructor called" << endl;
    delete firstName;
    delete lastName;
    delete dob;
}
/**
 * @brief Construct a new Tournament Member object
 * 
 * @param fn 
 * @param ln 
 * @param ndob 
 * @param ngender 
 */
TournamentMember::TournamentMember(char *fn, char *ln, char *ndob, int ID, string ngender)
{
    cout << "TournamentMember Parameterized constructor called" << endl;
    firstName = fn;
    lastName = ln;
    dob = ndob;
    memberID = ID;
    gender = ngender;
}
//service method
/**
 * @brief 
 * 
 */

//CHILD CLASS METHODS//

/**
 * @brief Construct a new Player object
 * 
 */
Player::Player()
{
    number = 0;
    position = "";
    goals = 0;
    foot = true;
}

/**
 * @brief Construct a new Player object
 * 
 * @param p 
 */
Player::Player(Player &p)
{
    number = p.number;
    position = p.position;
    goals = p.goals;
    foot = p.foot;
}
/**
 * @brief Construct a new Player object
 * 
 * @param num 
 * @param pos 
 * @param goalss 
 * @param nfoot 
 */
Player::Player(int num, string pos, int goalss, bool nfoot)
{
    cout << "Player Parameterized constructor called" << endl;
    number = num;
    position = pos;
    goals = goalss;
    foot = nfoot;
}
/**
 * @brief Construct a new Player object
 * 
 * @param fn 
 * @param ln 
 * @param ndob 
 * @param ID 
 * @param ngender 
 * @param num 
 * @param pos 
 * @param goalss 
 * @param nfoot 
 */
Player::Player(char *fn, char *ln, char *ndob, int ID, string ngender,
               int num, string pos, int goalss, bool nfoot)
{
    cout << "Player Parameterized constructor called" << endl;
    setFirstName(fn);
    setLastName(ln);
    setDob(ndob);
    setGender(ngender);
    setMemberId(ID);
    number = num;
    position = pos;
    goals = goalss;
    foot = nfoot;
}
/**
 * @brief Destroy the Player object
 * 
 */
Player::~Player()
{
    cout << "Player Player destructor called" << endl;
}
/**
 * @brief prints data
 * 
 */
void Player::toString()
{
    string line;
    if (foot == true)
    {
        line = "Right footed";
    }
    else
    {
        line = "Left footed";
    }

    cout << "Name: " << getFirstName() << " " << getLastName() << endl
         << "Date of Birth: " << getDob() << endl
         << "Gender: " << getGender() << endl
         << "Member ID: " << getMemberId() << endl
         << "Number: " << number << endl
         << "Position: " << position << endl
         << "Goals: " << goals << endl
         << "Dominant foot: " << line << endl
         << "Location: " << getLocation() << endl
         << endl;
}
/**
 * @brief increment goals
 * 
 */
void Player::incGoals(int g)
{
    goals += g;
}
