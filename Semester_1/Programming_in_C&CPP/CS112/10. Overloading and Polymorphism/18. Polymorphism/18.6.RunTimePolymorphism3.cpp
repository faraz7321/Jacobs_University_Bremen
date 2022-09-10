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
   
class Employee {
public:
	virtual void raiseSalary() {
		cout << "Common Salary raise applied. 5,000 ruppees." << endl; /* common raise salary code */
	}

	virtual void promote() { 
		cout << "Common promotion applied. Raised to next rank. " << endl; /* common promote code */ }
};

class Engineer : public Employee {
	void raiseSalary() {
		cout << "Engineer Salary raise applied. 6,000 ruppees." << endl; /* Engineer specific raise salary code, may contain
		increment of engineer specific incentives*/
	}

	virtual void promote() {
		cout << "Engineer promotion applied. Raised to Senior Engineer. " << endl; /* Engineer specific promote */
	}
};

class Manager : public Employee {
	virtual void raiseSalary() {
		cout << "Manager Salary raise applied. 10,000 ruppees." << endl; /* Manager specific raise salary code, may contain
		increment of manager specific incentives*/
	}

	virtual void promote() {
		cout << "Manager promotion applied. Raised to Head Manager. " << endl; /* Manager specific promote */
	}
};

class Clerk : public Employee {
	virtual void raiseSalary() {
		cout << "Clerk Salary raise applied. 2,000 ruppees." << endl; /* Clerk specific raise salary code, may contain
		increment of clerk specific incentives*/
	}

	virtual void promote() {
		cout << "Clerk promotion applied. Raised to Head Clerk. " << endl; /* Clerk specific promote */
	}
};

// Similarly, there may be other types of employees

// We need a very simple function to increment the salary of all employees
// Note that emp[] is an array of pointers and actual pointed objects can
// be any type of employees.
// This function should ideally be in a class like Organization,
// we have made it global to keep things simple
void globalRaiseSalary(Employee* emp[], int n)
{
	for (int i = 0; i < n; i++)

		// Polymorphic Call: Calls raiseSalary()
		// according to the actual object, not
		// according to the type of pointer
		emp[i]->raiseSalary();
}

int main() {
	Employee* emp[5];
	
	Clerk basheer, nazeer;
	Manager faqeer, lateef;
	Engineer AllahRakha;
	
	emp[0] = &basheer;
	emp[1] = &nazeer;
	emp[2] = &faqeer;
	emp[3] = &lateef;
	emp[4] = &AllahRakha;

	globalRaiseSalary(&emp[0],5);

}