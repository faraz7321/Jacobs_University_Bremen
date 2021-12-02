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
   
// Base class
class Shape {
    protected:
	    int length, width;

    public:
	    Shape(int l, int w) { // default constructor
		    length = l;
		    width = w;
	    } 
	
        int get_Area() {
	    	cout << "This is call to parent class area" << endl;
            return (length*width);
	    }
};

// Derived class
class Square : public Shape {
    public:
	    Square(int l = 0, int w = 0) : Shape(l, w) {
	    } // declaring and initializing derived class constructor
	    
        int get_Area() {
		    cout << "Square area: " << length * width << endl;
		    return (length * width);
	    }
};

// Derived class
class Rectangle : public Shape {
    public:
	    Rectangle(int l = 0, int w = 0): Shape(l, w) {
	    } // declaring and initializing derived class constructor
	
        int get_Area() {
		    cout << "Rectangle area: " << length * width << endl;
		    return (length * width);
    	}
};

int main(void) {
	Shape* s;
	Square sq(5, 5); // making object of child class Sqaure
	Rectangle rec(4, 5); // making object of child class Rectangle

	s = &sq;
	s->get_Area();
	s = &rec;
	s->get_Area();

	return 0;
}
