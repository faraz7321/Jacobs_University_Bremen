/*
CH-230-A
testcity.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "City.h"

int main()
{
    //Creating 3 instances of City with constructor
    City *Bremen = new City("Bremen", 569352, "Andreas Bovenschulte", 326.7);
    City *Paris = new City("Paris", 8423481, "Anne Hidalgo", 105.6);
    City *London = new City("London", 9312564, "Sadiq Khan", 1572);

    //prining elements of object
    Paris->toString();
    Bremen->toString();
    London->toString();

    //deleting the object instance
    delete Bremen;
    delete Paris;
    delete London;
    return 0;
}
