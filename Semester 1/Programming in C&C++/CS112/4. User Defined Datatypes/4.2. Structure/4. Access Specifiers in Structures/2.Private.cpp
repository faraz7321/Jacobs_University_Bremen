/**********************************************************************
 * Access specifiers define how the members (attributes and methods)  *
 * of a structure can be accessed. In C++, there are three access     *
 * specifiers:                                                        *
 *                                                                    *
 * public - members are accessible from outside the structure         *
 *                                                                    *
 * private - members cannot be accessed (or viewed) from outside the  *
 * structure                                                          *
 *                                                                    *
 * protected - members cannot be accessed from outside the structure, *
 * however, they can be accessed in inherited structures. You will    *
 * learn more about Inheritance later.                                *
 *                                                                    *
 * Note: By default, all members of a structure are public if you     *
 * don't specify an access specifier.                                 *
 **********************************************************************/

#include <iostream>

using namespace std;

// Create a Car structure with some attributes
struct Car {
/**********************************************************************
 * The public keyword is an access specifier. In the example below,   *
 * the members are public - which means that they can be accessed and *
 * modified from outside the code.                                    *
 *                                                                    *
 **********************************************************************/
  public:     // Public access specifier
    int x;    // Public attribute

/**********************************************************************
 * The private keyword is an access specifier. In the example below,  *
 * the members are private - which means that they cannot be accessed *
 * or modified from outside the code.                                 *
 **********************************************************************/
  private:   // Private access specifier
    int y;   // Private attribute
};

int main() {
  Car myObj;
  myObj.x = 25;  // Allowed (public)
  myObj.y = 50;  // Not allowed (private). If you try to access a private member, an error occurs.
  return 0;
}

