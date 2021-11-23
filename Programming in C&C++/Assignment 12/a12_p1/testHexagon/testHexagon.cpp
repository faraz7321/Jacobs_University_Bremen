/*
CH-230-A
testHexagon.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "Shapes.h"
int main()
{
    /*creating required instances
    of Hexagon class*/
    Hexagon h1(9, "blue");
    Hexagon h2(15, "green");
    Hexagon h3(h2);

    //printing color, area and perimeter of hexagons

    cout << "Hexagon 1\n";
    h1.toString();

    cout << "Hexagon 2\n";
    h2.toString();

    cout << "Hexagon 3\n";
    h3.toString();
    return 0;
}
