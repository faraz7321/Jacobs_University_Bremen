/***************************************************************************
 * Following is a simple way to create classes in a name space             *
 ***************************************************************************/

// A C++ program to demonstrate use of class 
// in a namespace 
#include <iostream> 
using namespace std; 

namespace ns 
{ 
	// A Class in a namespace 
	class champ 
	{ 
	public: 
		void display() 
		{ 
			cout << "ns::champ::display()\n"; 
		} 
	}; 
} 

int main() 
{ 
	// Creating Object of champ Class 
	ns::champ obj; 

	obj.display(); 

	return 0; 
} 
