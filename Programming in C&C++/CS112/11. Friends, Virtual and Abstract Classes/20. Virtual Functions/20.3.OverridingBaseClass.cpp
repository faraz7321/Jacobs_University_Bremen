/**********************************************************************
 * A virtual function is a member function in the base class that we  *
 * expect to redefine in derived classes.                             *
 * 
 * Basically, a virtual function is used in the base class in order to*
 * ensure that the function is overridden. This especially applies to *
 * cases where a pointer of base class points to an object of a 	  *
 * derived class.													  * 													  *
 **********************************************************************/
#include <iostream>

using namespace std;

class Base {
   public:
    virtual void print() {
        cout << "Base print" << endl;
    }
};

class Derived : public Base {
   public:
    void print() {
        cout << "Derived print" << endl;
    }
};

/**********************************************************************
 * Later, if we create a pointer of Base type to point to an object of*
 * Derived class and call the print() function, it calls the print()  *
 * function of the Base class.                                        *
 *                                                                    *
 * In other words, the member function of Base is not overridden. 	  *												  *
 **********************************************************************/
int main() {
    Derived derived1;
    Base* base1 = &derived1;

    // calls function of Base class
    base1->print();

    return 0;
}

/**********************************************************************
 * In order to avoid this, we declare the print() function of the Base*
 * class as virtual by using the virtual keyword.                     *
 * 
 * Here, we have declared the print() function of Base as virtual.    *
 * So, this function is overridden even when we use a pointer of Base *
 * type that points to the Derived object derived1.                   *
 **********************************************************************/
