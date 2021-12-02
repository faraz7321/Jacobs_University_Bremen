/**********************************************************************
 * Templates are powerful features of C++ which allows you to write   *
 * generic programs. In simple terms, you can create a single function* 
 * or a class to work with different data types using templates.      *
 * 																	  *
 * Templates are often used in larger codebase for the purpose of code* 
 * reusability and flexibility of the programs.						  *
 * 																	  *
 * The concept of templates can be used in two different ways:		  *
 * Function Templates												  *
 * Class Templates													  *
 * 																	  *
 * A function template works in a similar to a normal function, with  *
 * one key difference.												  *
 * 																	  *
 * A single function template can work with different data types at   *
 * once but, a single normal function can only work with one set of   *
 * data types.														  *
 * 																	  *
 * Normally, if you need to perform identical operations on two or    *
 * more types of data, you use function overloading to create two     *
 * functions with the required function declaration.				  *
 * 																	  *
 * However, a better approach would be to use function templates      *
 * because you can perform the same task writing less and maintainable*
 * code.															  *
 * 																	  *
 * A function template starts with the keyword template followed by   *
 * template parameter/s inside  < > which is followed by function     *
 * declaration.														  *
 * 																	  *
 * In the code, T is a template argument that accepts different data  *
 * types (int, float), and class is a keyword.						  *
 * 																	  *
 * You can also use keyword typename instead of class in the          *
 * example.															  *
 * 																	  *
 * When, an argument of a data type is passed to someFunction( ),     *
 * compiler generates a new version of someFunction() for the given   *
 * data type.     													  *
 **********************************************************************/

// If two characters are passed to function template, character with larger ASCII value is displayed.

#include <iostream>
using namespace std;

// template function
template <class T>
T Large(T n1, T n2)
{
	return (n1 > n2) ? n1 : n2;
}

int main()
{
	int i1, i2;
	float f1, f2;
	char c1, c2;

	cout << "Enter two integers:\n";
	cin >> i1 >> i2;
	cout << Large(i1, i2) <<" is larger." << endl;

	cout << "\nEnter two floating-point numbers:\n";
	cin >> f1 >> f2;
	cout << Large(f1, f2) <<" is larger." << endl;

	cout << "\nEnter two characters:\n";
	cin >> c1 >> c2;
	cout << Large(c1, c2) << " has larger ASCII value.";

	return 0;
}

/**********************************************************************
 * In the above program, a function template Large() is defined that  *
 * accepts two arguments n1 and n2 of data type T. T signifies that   *
 * argument can be of any data type.                                  *
 * 																	  *
 * Large() function returns the largest among the two arguments using *
 * a simple conditional operation.									  *
 * 
 * Inside the main() function, variables of three different data      *
 * types: int, float and char are declared. The variables are then    *
 * passed to the Large() function template as normal functions.       *
 * 
 * During run-time, when an integer is passed to the template         *
 * function, compiler knows it has to generate a Large() function to  *
 * accept the int arguments and does so.                              *
 * 
 * Similarly, when floating-point data and char data are passed, it   *
 * knows the argument data types and generates the Large() function   *
 * accordingly.														  *
 * 
 * This way, using only a single function template replaced three     *
 * identical normal functions and made your code maintainable.	 	  *
 **********************************************************************/