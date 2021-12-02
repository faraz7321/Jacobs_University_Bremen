/****************************************************************************************************
 * Class can also be declared inside namespace and defined outside namespace using following syntax *
 ****************************************************************************************************/

// A C++ program to demonstrate use of class 
// in a namespace 
#include <iostream> 
using namespace std; 

namespace ns 
{ 
	// Only declaring class here 
	class champ; 
} 

// Defining class outside 
class ns::champ 
{ 
public: 
	void display() 
	{ 
		cout << "ns::champ::display()\n"; 
	} 
}; 

int main() 
{ 
	//Creating Object of champ Class 
	ns::champ obj; 
	obj.display(); 
	return 0; 
} 
