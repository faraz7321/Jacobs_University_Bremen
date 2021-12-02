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

#include <iostream>
#include <string>
using namespace std;

// Base class
class Animal {
  public:
    void animalSound() {
      cout << "The animal makes a sound \n" ;
    }

    void Virtual walk();
};

// Derived class
// Now we can create Pig and Dog objects and override the animalSound() method:
// Remember from the Inheritance lecture that we use the : symbol to inherit from a class.
class Pig : public Animal {
  public:
    void animalSound() {
      cout << "The pig says: wee wee \n" ;
    }

    void walk() {
      cout << "I walk on four legs" << endl;
    }
};

// Derived class
class Dog : public Animal {
  public:
    void animalSound() {
      cout << "The dog says: bow wow \n" ;
    }
};

int main() {
  Animal myAnimal;
  Pig myPig;
  Dog myDog;

  myAnimal.animalSound();
  myPig.animalSound();
  myDog.animalSound();
  myPig.walk();
  return 0;
}

// Why And When To Use "Inheritance" and "Polymorphism"?
// It is useful for code reusability: reuse attributes and methods of an existing class when you create a new class.