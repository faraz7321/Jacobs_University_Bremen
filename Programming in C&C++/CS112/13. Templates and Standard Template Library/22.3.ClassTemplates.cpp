/**********************************************************************
 * Like function templates, you can also create class templates for   *
 * generic class operations.                                          *
 * Sometimes, you need a class implementation that is same for all    *
 * classes, only the data types used are different.					  *
 * 																	  *
 * Normally, you would need to create a different class for each data *
 * type OR create different member variables and functions within a   *
 * single class.													  *
 * 																	  *
 * This will unnecessarily bloat your code base and will be hard to   *
 * maintain, as a change is one class/function should be performed on *
 * all classes/functions.											  *
 * 																	  *
 * However, class templates make it easy to reuse the same code for   *
 * all data types.													  *
 **********************************************************************/

#include <iostream>
using namespace std;

template <class T>
class Calculator
{
private:
	T num1, num2;
	
public:
	Calculator(T n1, T n2)
	{
		num1 = n1;
		num2 = n2;
	}
	
	void displayResult()
	{
		cout << "Numbers are: " << num1 << " and " << num2 << "." << endl;
		cout << "Addition is: " << add() << endl;
		cout << "Subtraction is: " << subtract() << endl;
		cout << "Product is: " << multiply() << endl;
		cout << "Division is: " << divide() << endl;
	}
	
	T add() { return num1 + num2; }
	
	T subtract() { return num1 - num2; }
	
	T multiply() { return num1 * num2; }
	
	T divide() { return num1 / num2; }
};

int main()
{
	Calculator<int> intCalc(2, 1);
	Calculator<float> floatCalc(2.4, 1.2);
	
	cout << "Int results:" << endl;
	intCalc.displayResult();
	
	cout << endl << "Float results:" << endl;
	floatCalc.displayResult();
	
	return 0;
}

/**********************************************************************
 * In the above program, a class template Calculator is declared.	  *
 * 																	  *
 * The class contains two private members of type T: num1 & num2, and *
 * a constructor to initalize the members.							  *
 * 																	  *
 * It also contains public member functions to calculate the addition,*
 * subtraction, multiplication and division of the numbers which      *
 * return the value of data type defined by the user. Likewise, a     *
 * function displayResult() to display the final output to the screen.*
 * 																	  *
 * In the main() function, two different Calculator objects intCalc   *
 * and floatCalc are created for data types: int and float            *
 * respectively. The values are initialized using the constructor.	  *
 * 																	  *
 * Notice we use <int> and <float> while creating the objects. These  *
 * tell the compiler the data type used for the class creation.		  *
 * 																	  *
 * This creates a class definition each for int and float, which are  *
 * then used accordingly.											  *
 * 																	  *
 * Then, displayResult() of both objects is called which performs the *
 * Calculator operations and displays the output.					  *
 **********************************************************************/
