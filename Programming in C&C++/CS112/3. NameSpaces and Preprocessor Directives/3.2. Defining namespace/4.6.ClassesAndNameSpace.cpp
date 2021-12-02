/***********************************************************************************
 * We can define methods also outside the namespace. Following is an example code. *
 ***********************************************************************************/

// A C++ code to demonstrate that we can define 
// methods outside namespace. 
#include <iostream> 
using namespace std; 

// Creating a namespace 
namespace ns 
{ 
	void display(); 
	class champ 
	{ 
	public: 
		void display(); 
	}; 
} 

// Defining methods of namespace 
void ns::champ::display() 
{ 
	cout << "ns::champ::display()\n"; 
} 
void ns::display() 
{ 
	cout << "ns::display()\n"; 
} 

// Driver code 
int main() 
{ 
	ns::champ obj; 
	ns::display(); 
	obj.display(); 
	return 0; 
} 
