#include <iostream>
#include <cstdlib>
#include "Critter.h"

// using namespace std;
//  either use namespace std or
//  write the code like this
//  std::string as string is part of std namespace

int main(int argc, char **argv)
{
    Critter c;

    std::string name;
    int hunger;

    std::cout << std::endl
              << "Please enter data: " << std::endl;
    std::cout << "Name: ";
    // cin >> name; will not work if name contains
    // spaces
    std::getline(std::cin, name);
    c.setName(name);
    std::cout << "Hunger: ";
    std::cin >> hunger;
    c.setHunger(hunger);

    std::cout << "You have created:" << std::endl;
    c.print();
    return 0;
}