/**********************************************************************
 * Access specifiers define how the members (attributes and methods)  *
 * of a class can be accessed. In C++, there are three access         *
 * specifiers:                                                        *
 *                                                                    *
 * public - members are accessible from outside the class             *
 *                                                                    *
 * private - members cannot be accessed (or viewed) from outside the  *
 * class                                                              *
 *                                                                    *
 * protected - members cannot be accessed from outside the class,     *
 * however, they can be accessed in inherited classes. You will learn *
 * more about Inheritance later.                                      *
 *                                                                    *
 * Note: By default, all members of a class are private if you don't  *
 * specify an access specifier.                                       *
 **********************************************************************/

#include <iostream>

using namespace std;

// Create a Car class with some attributes
class Car {
/**********************************************************************
 * The public keyword is an access specifier. In the example below,   *
 * the members are public - which means that they can be accessed and *
 * modified from outside the code.                                    *
 *                                                                    *
 * public - members are accessible from outside the class             *
 *                                                                    *
 * private - members cannot be accessed (or viewed) from outside the  *
 * class                                                              *
 *                                                                    *
 * protected - members cannot be accessed from outside the class,     *
 * however, they can be accessed in inherited classes. You will learn *
 * more about Inheritance later.                                      *
 *                                                                    *
 **********************************************************************/
  public:
    string brand;   
    string model;
    int year;
};

int main() {
  // Create an object of Car
  Car carObj1;
  carObj1.brand = "BMW";
  carObj1.model = "X5";
  carObj1.year = 1999;

  // Create another object of Car
  Car carObj2;
  carObj2.brand = "Ford";
  carObj2.model = "Mustang";
  carObj2.year = 1969;

  // Print attribute values
  cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << "\n";
  cout << carObj2.brand << " " << carObj2.model << " " << carObj2.year << "\n";
  return 0;
}
