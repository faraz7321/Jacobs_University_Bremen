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
 * 																	  *
 * Runtime polymorphism is achieved only through a pointer (or 		  *
 * reference) of base class type. Also, a base class pointer can point*
 * to the objects of base class as well as to the objects of derived  *
 * class. In the code below, base class pointer ‘p’ contains the      *
 * address of object ‘obj1’ of derived class.						  *
 * 																	  *
 * Late binding(Runtime) is done in accordance with the content of    *
 * pointer (i.e. location pointed to by pointer) and Early            *
 * binding(Compile time) is done according to the type of pointer,    *
 * since print() function is declared with virtual keyword so it will *
 * be bound at run-time (output is print derived class as pointer is  *
 * pointing to object of derived class ) and show() is non-virtual so *
 * it will be bound during compile time(output is show base class as  *
 * pointer is of base type ).										  *
 * 																	  *
 * NOTE: If we have created a virtual function in the base class and  *
 * it is being overridden in the derived class then we don’t need     *
 * virtual keyword in the derived class, functions are automatically  *
 * considered as virtual functions in the derived class.              *
 *																	  *
 * A virtual function is a member function which is declared within a *
 * base class and is re-defined(Overriden) by a derived class. When   *
 * you refer to a derived class object using a pointer or a reference *
 * to the base class, you can call a virtual function for that object *
 * and execute the derived class’s version of the function. 		  *
 * 																	  *
 * Virtual functions ensure that the correct function is called for an*
 * object, regardless of the type of reference (or pointer) used for  *
 * function call.													  *
 * 																	  *
 * Virtual functions are mainly used to achieve Runtime polymorphism. *
 * 																	  *
 * Functions are declared with a virtual keyword in base class.		  *
 * 																	  *
 * The resolving of function call is done at Run-time.				  *
 * 																	  *
 * Some Rules for Virtual Functions                                   *
 * 1. Virtual functions cannot be static.							  *
 * 2. A virtual function can be a friend function of another class.   *
 * 3. Virtual functions should be accessed using pointer or reference *
 * of base class type to achieve run time polymorphism.               *
 * 4. The prototype of virtual functions should be the same in the    *
 * base as well as derived class.									  *
 * 5. They are always defined in the base class and overridden in a   *
 * derived class. It is not mandatory for the derived class to        *
 * override (or re-define the virtual function), in that case, the    *
 * base class version of the function is used.						  *
 * 6. A class may have virtual destructor but it cannot have a virtual*
 * constructor.														  *
 **********************************************************************/

#include <iostream>
using namespace std;

class base {
public:
	void fun_1() { cout << "base-1\n"; }
	virtual void fun_2() { cout << "base-2\n"; }
	virtual void fun_3() { cout << "base-3\n"; }
	virtual void fun_4() { cout << "base-4\n"; }
};

class derived : public base {
public:
	void fun_1() { cout << "derived-1\n"; }
	void fun_2() { cout << "derived-2\n"; }
	void fun_4(int x) { cout << "derived-4\n"; }
};

int main()
{
	base* p;
	derived obj1;
	p = &obj1;

	// Early binding because fun1() is non-virtual
	// in base
	p->fun_1();

	// Late binding (RTP)
	p->fun_2();

	// Late binding (RTP)
	p->fun_3();

	// Late binding (RTP)
	p->fun_4();

	// Early binding but this function call is illegal(produces error) because pointer
	// is of base type and function is of derived class
	// p->fun_4(5);
}
