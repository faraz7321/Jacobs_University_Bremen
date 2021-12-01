#include "Creature.h"
using namespace std;
int main()
{
    //creating a creature
    Creature c;
    c.run();

    //Creating a wizard
    Wizard w;
    w.run();
    w.hover();

    //creating a dementor
    Dementor d;
    d.run();
    d.eats();

    //creating an elf
    Elf e;
    e.setName("Dobby");
    e.run();
    e.status();

    return 0;
}