/**********************************************************************
 * When executing C++ code, different errors can occur: coding errors *
 * made by the programmer, errors due to wrong input, or other        *
 * unforeseeable things.											  *
 * 																	  *
 * When an error occurs, C++ will normally stop and generate an error *
 * message. The technical term for this is: C++ will throw an         *
 * exception (throw an error).										  *
 * 																	  *
 * Exception handling in C++ consist of three keywords: try, throw and*
 * catch:															  *
 * 																	  *
 * The try statement allows you to define a block of code to be tested*
 * for errors while it is being executed.							  *
 * 																	  *
 * The throw keyword throws an exception when a problem is detected,  *
 * which lets us create a custom error.								  *
 * 																	  *
 * The catch statement allows you to define a block of code to be     *
 * executed, if an error occurs in the try block.					  *
 * 																	  *
 * The try and catch keywords come in pairs.						  *
 * 																	  *
 * Consider the following example:									  *
 **********************************************************************/

#include <iostream>
using namespace std;

int main()
{
	try {
  		int age = 15;
  		if (age >= 18) {
    		
  		} else {
    		throw (age);
  		}
		cout << "Access granted - you are old enough.";
	} 
	catch (int myNum) {
  		cout << "Access denied - You must be at least 18 years old.\n";
  		cout << "Age is: " << myNum;
	}

	return 0;
}

/**********************************************************************
 * We use the try block to test some code: If the age variable is less*
 * than 18, we will throw an exception, and handle it in our catch    *
 * block.															  *
 * 																	  *
 * In the catch block, we catch the error and do something about it.  *
 * The catch statement takes a parameter: in our example we use an int*
 * variable (myNum) (because we are throwing an exception of int type *
 * in the try block (age)), to output the value of age.				  *
 *																	  *
 * If no error occurs (e.g. if age is 20 instead of 15, meaning it    *
 * will be be greater than 18), the catch block is skipped:			  *
 **********************************************************************/