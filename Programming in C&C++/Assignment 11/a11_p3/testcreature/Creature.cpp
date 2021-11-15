/*
CH-230-A
Creature.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "Creature.h"
Creature::Creature() : distance(10)
{
    cout << "Creating a Creature.\n";
}

void Creature::run() const
{
    cout << "running " << distance << " meters!\n";
}

Wizard::Wizard() : distFactor(3)
{
    cout << "\nCreating a Wizard.\n";
}

void Wizard::hover() const
{
    cout << "hovering " << (distFactor * distance) << " meters!\n";
}
Dementor::Dementor()
{
    cout << "\nCreating a dementor.\n";
    feed = "Harry Potter";
}
void Dementor::eats()
{
    cout << "feeding on flesh of " << feed << endl;
}
Dementor::~Dementor()
{
}
Elf::Elf()
{
    cout << "\nCreating an elf.\n";
    isSlave = false;
}
void Elf::setName(string newname)
{
    name = newname;
}

Elf::~Elf()
{
}
void Elf::status()
{
    if (isSlave)
    {
        cout << name << " is a slave\n";
    }
    else
    {
        cout << name << " is free\n";
    }
}