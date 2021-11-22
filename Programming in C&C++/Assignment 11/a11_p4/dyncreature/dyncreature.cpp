/*
CH-230-A
dyncreature.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */

#include <iostream>
#include <string>
#include "Creature.h"

using namespace std;

int main()
{
    while (true)
    {
        // Get user input
        string input;
        getline(cin, input);

        if (input == "wizard") // wizard created
        {
            Wizard *w = new Wizard();
            w->hover();
            delete w;
        }
        else if (input == "object1" || input == "dementor") // dementor created
        {
            Dementor *d = new Dementor();
            d->eats();
            delete d;
        }
        else if (input == "object2" || input == "elf") // elf created
        {
            Elf *e = new Elf();
            e->status();
            delete e;
        }
        else if (input == "quit")
        {
            exit(0);
        }
    }

    return 0;
}