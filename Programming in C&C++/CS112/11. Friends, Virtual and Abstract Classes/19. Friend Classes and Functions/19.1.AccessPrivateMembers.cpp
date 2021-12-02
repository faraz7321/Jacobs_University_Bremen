/**********************************************************************
 * Data hiding is fundamental concept of object-oriented programming. *
 * It restricts the access of private members from outside of the     *
 * class.                                                             *
 *																	  *
 * Similarly, protected members can only be accessed by derived       *
 * classes and are inaccessible from outside. For example, the        *
 * following code generates error because we try to access private    *
 * members.															  *
 **********************************************************************/

#include <iostream>
using namespace std;

class MyClass {
    private:
        int member1;
}

int main() {
    MyClass obj;

    // Error! Cannot access private members from here.
    obj.member1 = 5;
}