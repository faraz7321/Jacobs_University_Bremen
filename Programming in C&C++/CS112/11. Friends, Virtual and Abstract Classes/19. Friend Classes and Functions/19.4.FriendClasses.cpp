/**********************************************************************
 * We can also use a friend Class in C++ using the friend keyword.    *
 *                                                                    *
 * When a class is declared a friend class, all the member functions  *
 * of the friend class become friend functions.                       *
 * 
 * Since ClassB is a friend class, we can access all members of ClassA*
 * from inside ClassB.                                                *
 * 
 * However, we cannot access members of ClassB from inside ClassA. It *
 * is because friend relation in C++ is only granted, not taken.      *
 * 
 * Here, ClassB is a friend class of ClassA. So, ClassB has access to *
 * the members of classA.                                             *
 *                                                                    *
 * In ClassB, we have created a function add() that returns the sum of* 
 * numA and numB.                                                     *
 * 
 * Since ClassB is a friend class, we can create objects of ClassA    *
 * inside of ClassB.                                                  *
 **********************************************************************/

// C++ program to demonstrate the working of friend class

#include <iostream>
using namespace std;

// forward declaration
class ClassB;

class ClassA {
    private:
        int numA;

        // friend class declaration
        friend class ClassB;

    public:
        // constructor to initialize numA to 12
        ClassA() : numA(12) {}
};

class ClassB {
    private:
        int numB;

    public:
        // constructor to initialize numB to 1
        ClassB() : numB(1) {}
    
    // member function to add numA
    // from ClassA and numB from ClassB
    int add() {
        ClassA objectA;
        return objectA.numA + numB;
    }
};

int main() {
    ClassB objectB;
    cout << "Sum: " << objectB.add() << endl;
    return 0;
}