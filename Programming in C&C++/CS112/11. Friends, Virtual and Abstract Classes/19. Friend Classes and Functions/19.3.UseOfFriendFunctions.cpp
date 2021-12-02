/**********************************************************************
 * However, there is a feature in C++ called friend functions that    *
 * break this rule and allow us to access member functions from       *
 * outside the class.                                                 *
 *                                                                    *
 * Similarly, there is a friend class as well, which we will learn    *
 * later                                                              *
 *                                                                    *
 * A friend function can access the private and protected data of a   *
 * class. We declare a friend function using the friend keyword inside*
 * the body of the class.                                             *
 * 
 * Here, addFive() is a friend function that can access both private  *
 * and public data members.                                           *
 *                                                                    *
 * Though this example gives us an idea about the concept of a friend *
 * function, it doesn't show any meaningful use.                      *
 *
 * A more meaningful use would be operating on objects of two         *
 * different classes. That's when the friend function can be very     *
 * helpful.                                                           *
 *                                                                    *
 * In this program, ClassA and ClassB have declared add() as a friend *
 * function. Thus, this function can access private data of both      *
 * classes.                                                           *
 *                                                                    *
 * One thing to notice here is the friend function inside ClassA is   *
 * using the ClassB. However, we haven't defined ClassB at this point.*
 * For this to work, we need a forward declaration of ClassB in our   *
 * program.                                                           *
 **********************************************************************/

// Add members of two different classes using friend functions

#include <iostream>
using namespace std;

// forward declaration
class ClassB;

class ClassA {
    
    public:
        // constructor to initialize numA to 12
        ClassA() : numA(12) {}
        
    private:
        int numA;
        
         // friend function declaration
         friend int add(ClassA, ClassB);
};

class ClassB {

    public:
        // constructor to initialize numB to 1
        ClassB() : numB(1) {}
    
    private:
        int numB;
 
        // friend function declaration
        friend int add(ClassA, ClassB);
};

// access members of both classes
int add(ClassA objectA, ClassB objectB) {
    return (objectA.numA + objectB.numB);
}

int main() {
    ClassA objectA;
    ClassB objectB;
    cout << "Sum: " << add(objectA, objectB) << endl;
    return 0;
}