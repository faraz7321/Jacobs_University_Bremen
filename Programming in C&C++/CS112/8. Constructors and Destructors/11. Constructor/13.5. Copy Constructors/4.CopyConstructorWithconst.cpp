/**********************************************************************
 * Following is a complete C++ program to demonstrate use of Copy     *
 * constructor. In the following String class, we must write copy     *
 * constructor.                                                       *
 **********************************************************************/

#include<iostream>
using namespace std;

class Test
{
	/* Class data members */
	public:
		Test(const Test &t) { /* Copy data members from t*/}
		Test()	 { /* Initialize data members */ }
};

Test fun()
{
	cout << "fun() Called\n";
	Test t;
	return t;
}

int main()
{
	Test t1;
	Test t2 = fun();
	return 0;
}
