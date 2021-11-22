/*
CH-230-A
testshapes.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */

#include <iostream>
#include "Shapes.h"

using namespace std;
int main(int argc, char **argv)
{

   Circle c("First circle", 3, 4, 7);
   RegularPolygon r("TRIANGLE", 1, 1, 3);

   r.printName();
   c.printName();

   cout << "\nArea of circle is " << c.area() << "\n";
   cout << "Perimeter of Circle is " << c.perimeter() << "\n";

   // Creating a rectangle
   Rectangle rr("first rectangle", 0, 0, 3, 4);
   cout << "\nArea of first rectangle is " << rr.area() << "\n";
   cout << "Perimeter of first rectangle is " << rr.perimeter() << "\n";

   // Creating square
   Square s("first square", 0, 0, 8);
   cout << "\nArea of first square is " << s.area() << "\n";
   cout << "Perimeter of first square is " << s.perimeter() << "\n";
}