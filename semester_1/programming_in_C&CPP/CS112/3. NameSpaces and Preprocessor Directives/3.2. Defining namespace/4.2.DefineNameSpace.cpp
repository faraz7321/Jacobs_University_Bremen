// In each scope, a name can only represent one entity. So, there cannot be two variables with the same name in the same scope. 
// Using namespaces, we can create two variables or member functions having the same name.

// Here we can see that more than one variables 
// are being used without reporting any error. 
// That is because they are declared in the 
// different namespaces and scopes. 
#include <iostream> 
using namespace std; 

// Variable created inside namespace 
namespace first 
{ 
	int val = 500; 
} 

// Global variable 
int val = 100; 

int main() 
{ 
	// Local variable 
	int val = 200; 

	// These variables can be accessed from 
	// outside the namespace using the scope 
	// operator :: 
	cout << val << '\n'; 

	return 0; 
} 
