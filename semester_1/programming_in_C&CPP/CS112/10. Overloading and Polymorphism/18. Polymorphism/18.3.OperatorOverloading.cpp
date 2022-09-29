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

/**********************************************************************
 * Operator Overloading: C++ also provide option to overload          *
 * operators. For example, we can make the operator (‘+’) for string  *
 * class to concatenate two strings. We know that this is the addition*
 * operator whose task is to add two operands. So a single operator   *
 * ‘+’ when placed between integer operands , adds them and when      *
 * placed between string operands, concatenates them.                 *
 **********************************************************************/

#include<iostream> 
using namespace std; 
   
class Complex { 
private: 
    int real, imag; 
public: 
    Complex(int r = 0, int i =0)  {real = r;   imag = i;} 
       
    // This is automatically called when '+' is used with 
    // between two Complex objects 
    Complex operator + (Complex const &obj) { 
         Complex res; 
         res.real = real + obj.real; 
         res.imag = imag + obj.imag; 
         return res; 
    } 
    void print() { cout << real << " + i" << imag << endl; } 

    // This is automatically called when '==' is used with 
    // between two Complex objects 
    bool operator == (Complex const &obj) {
        if(real == obj.real && imag == obj.imag)
            return true;
        else 
            return false; 
    }

    bool isEqual (Complex const &obj) {
        if(real == obj.real && imag == obj.imag)
            return true;
        else 
            return false; 
    } 
}; 
   
int main() 
{ 
    Complex c1(10, 5), c2(10, 4); 
    Complex c3 = c1 + c2; // An example call to "operator+" 
    c3.print(); 
    
    if(c1 == c2) 
        cout << "Both complex numbers are equal." << endl;
    else
        cout << "Both complex numbers are not equal" << endl; 

    if(c1.isEqual(c2)) 
        cout << "Both complex numbers are equal." << endl;
    else
        cout << "Both complex numbers are not equal" << endl; 

} 
