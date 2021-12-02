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

#include <iostream>
using namespace std;

template <typename T>
void Swap(T &n1, T &n2)
{
	T temp;
	temp = n1;
	n1 = n2;
	n2 = temp;
}

int main()
{
	int i1 = 1, i2 = 2;
	float f1 = 1.1, f2 = 2.2;
	char c1 = 'a', c2 = 'b';

	cout << "Before passing data to function template.\n";
	cout << "i1 = " << i1 << "\ni2 = " << i2;
	cout << "\nf1 = " << f1 << "\nf2 = " << f2;
	cout << "\nc1 = " << c1 << "\nc2 = " << c2;

	Swap(i1, i2);
	Swap(f1, f2);
	Swap(c1, c2);

    cout << "\n\nAfter passing data to function template.\n";
	cout << "i1 = " << i1 << "\ni2 = " << i2;
	cout << "\nf1 = " << f1 << "\nf2 = " << f2;
	cout << "\nc1 = " << c1 << "\nc2 = " << c2 << endl;

	return 0;
}

/**********************************************************************
 * In this program, instead of calling a function by passing a value, *
 * a call by reference is issued. 									  *
 * 																	  *
 * The Swap() function template takes two arguments and swaps them by *
 * reference. 														  *
 **********************************************************************/
