/*
CH-230-A
TournamentMember.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#pragma once
#include <iostream>
using namespace std;

//PARENT CLASS//
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
    TournamentMember(char *fn, char *ln, char *dob, int ID, string ngender);
    ~TournamentMember();
    //inline getter and setter methods
    inline string getFirstName() const { return firstName; }
    inline string getLastName() const { return lastName; }
    inline string getDob() const { return dob; }
    inline int getMemberId() const { return memberID; }
    inline string getGender() { return gender; }
    inline static string getLocation() { return location; }
    inline void setFirstName(char *fn) { firstName = fn; }
    inline void setLastName(char *ln) { lastName = ln; }
    inline void setDob(char *ndob) { dob = ndob; }
    inline void setMemberId(int id) { memberID = id; }
    inline void setGender(string newgender) { gender = newgender; }
    inline static void setLocation(string loc) { location = loc; }
};

//CHILD CLASS//

class Player : public TournamentMember
{
private:
    int number;
    string position;
    int goals;
    bool foot;

public:
    //constructors
    Player();
    Player(Player &);
    Player(int, string, int, bool);
    Player(char *fn, char *ln, char *ndob, int ID, string ngender,
           int num, string pos, int goalss, bool nfoot);
    //destructor
    ~Player();
    //inline getters and setters
    inline int getNumber() const { return number; }
    inline string getPosition() const { return position; }
    inline int getGoals() const { return goals; }
    inline bool getFoot() const { return foot; }
    inline void setNumber(int n) { number = n; }
    inline void setPosition(string pos) { position = pos; }
    inline void setFoot(bool f) { foot = f; }
    //service method
    void toString();
    void incGoals(int g);
};
