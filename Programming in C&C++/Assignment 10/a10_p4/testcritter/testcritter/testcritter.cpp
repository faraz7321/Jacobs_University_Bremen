/*
CH-230-A
testcritter.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <cstdlib>
#include "Critter.h"

using namespace std;

int main(int argc, char **argv)
{
    Critter c1 = Critter();
    c1.setHunger(2);
    c1.print();

    Critter c2 = Critter("Faraz");
    c1.setHunger(2);
    c2.print();

    Critter c3 = Critter("Ahmad", 2, 8, 6.1);
    c3.print();

    //Critter c4 = Critter("Ahmad", 2, 8);
    //c4.print();
    return 0;
}