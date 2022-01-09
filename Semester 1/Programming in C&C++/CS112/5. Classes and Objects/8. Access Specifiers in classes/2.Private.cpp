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

// In the following example, we demonstrate the differences between public and private members:
class MyClass {
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
  public:    // Public access specifier
    int x;   // Public attribute
/**********************************************************************
 * The private keyword is an access specifier. In the example below,  *
 * the members are private - which means that they cannot be accessed *
 * or modified from outside the code.                                 *
 **********************************************************************/
  private:   // Private access specifier
    int y;   // Private attribute
};

int main() {
  MyClass myObj;
  myObj.x = 25;  // Allowed (public)
  myObj.y = 50;  // Not allowed (private). If you try to access a private member, an error occurs.
  return 0;
}

