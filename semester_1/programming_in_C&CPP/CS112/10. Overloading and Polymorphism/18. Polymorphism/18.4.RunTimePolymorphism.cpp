/**********************************************************************
 * The word polymorphism means having many forms. In simple words, we *
 * can define polymorphism as the ability of a message to be displayed*
 * in more than one form. A real-life example of polymorphism, a      *
 * person at the same time can have different characteristics. Like a *
 * man at the same time is a father, a husband, an employee. So the   *
 * same person posses different behavior in different situations. This*
 * is called polymorphism. Polymorphism is considered as one of the   *
 * important features of Object Oriented Programming.                 *
 *                                                                    *
 * In C++ polymorphism is mainly divided into two types:              *
 * Compile time Polymorphism                                          *
 * Runtime Polymorphism                                               *
 *                                                                    *
 * Compile Time Polymorphism can be further divided into two types    *
 * Function Overloading                                               *
 * Operator Overloading                                               *
 *                                                                    *
 * Run Time Polymorphism is displayed by Virtual Functions            *
 **********************************************************************/

#include<iostream> 
using namespace std; 
   
// C++ program for function overriding
class base
{
public:
	virtual void print () { 
        cout<< "print base class" << endl; 
    }

	virtual void show () { 
        cout<< "show base class" << endl; 
    }
};

class derived:public base
{
public:
	void print () { //print () is already virtual function in derived class, we could also declared as virtual void print () explicitly 
        cout<< "print derived class" <<endl; 
    }

    void show () { 
        cout<< "show derived class" <<endl; 
    }
};

//main function
int main() {
	base *bptr;
	derived d;
	bptr = &d;
	
	//virtual function, binded at runtime (Runtime polymorphism)
	bptr->print();
	
	// Non-virtual function, binded at compile time
	bptr->show();

    base b;
    bptr = &b;

    //virtual function, binded at runtime (Runtime polymorphism)
    bptr->print();
    // Non-virtual function, binded at compile time
    bptr->show();

	return 0;
}
