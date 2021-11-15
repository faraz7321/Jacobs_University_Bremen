/*
CH-230-A
Creature.h
Faraz Ahmad
fahmad@jacobs.university.de
 */

//Parent class
#include <iostream>
using namespace std;
class Creature
{
public:
    Creature();
    void run() const;

protected:
    int distance;
};

//child class
class Wizard : public Creature
{
public:
    Wizard();
    void hover() const;

private:
    int distFactor;
};
//CHILD CLASS
class Dementor : public Creature
{
private:
    string feed;

public:
    Dementor();
    ~Dementor();
    void eats();
};

//CHILD CLASS
class Elf : public Creature
{
private:
    bool isSlave;
    string name;

public:
    Elf();
    void setName(string name);
    ~Elf();
    void status();
};
