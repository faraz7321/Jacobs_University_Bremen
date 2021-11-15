/*
CH-230-A
testshapes.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "Shapes.h"
using namespace std;
int main(int argc, char **argv)
{

   Circle c("first circle", 3, 4, 7);
   RegularPolygon r("TRIANGLE", 1, 1, 3);

   r.printName();
   c.printName();
}