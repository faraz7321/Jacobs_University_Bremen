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
 **********************************************************************/

// C++ program to demonstrate the working of friend function

#include <iostream>
using namespace std;

class Distance {
    private:
        int meter;
        
        // friend function
        friend int addFive(Distance);

    public:
        Distance() : meter(0) {}
        
};

// friend function definition
int addFive(Distance d) {

    //accessing private members from the friend function
    d.meter += 5;
    return d.meter;
}

int main() {
    Distance D;
    cout << "Distance: " << addFive(D) << endl;
    return 0;
}