/**********************************************************************
 * Polymorphism means "many forms", and it occurs when we have many   *
 * classes that are related to each other by inheritance.             *
 *                                                                    *
 * Like we specified in the previous chapter; Inheritance lets us     *
 * inherit attributes and methods from another class. Polymorphism    *
 * uses those methods to perform different tasks. This allows us to   *
 * perform a single action in different ways.                         *
 *                                                                    *
 * For example, think of a base class called Animal that has a method *
 * called animalSound(). Derived classes of Animals could be Pigs,    *
 * Cats, Dogs, Birds - And they also have their own implementation of *
 * an animal sound (the pig oinks, and the cat meows, etc.):          *
 *                                                                    *
 * This is an example of function overloading                         *
 **********************************************************************/

#include <iostream>
#include <string>
  
using namespace std; 
class Polymorph 
{ 
    public: 
      
    // function with 1 int parameter 
    void func(int x) 
    { 
        cout << "value of x is " << x << endl; 
    } 
      
    // function with same name but 1 double parameter 
    void func(double x) 
    { 
        cout << "value of x is " << x << endl; 
    } 
      
    // function with same name and 2 int parameters 
    void func(int x, int y) 
    { 
        cout << "value of x and y is " << x << ", " << y << endl; 
    } 
}; 
  
int main() { 
      
    Polymorph obj1; 
      
    // Which function is called will depend on the parameters passed 
    // The first 'func' is called  
    obj1.func(7); 
      
    // The second 'func' is called 
    obj1.func(9.132); 
      
    // The third 'func' is called 
    obj1.func(85,64); 
    return 0; 
}  

// In the above example, a single function named func acts differently in three different situations which is the property of polymorphism.