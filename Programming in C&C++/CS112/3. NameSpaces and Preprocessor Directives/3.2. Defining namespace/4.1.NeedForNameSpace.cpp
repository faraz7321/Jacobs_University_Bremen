// A program to demonstrate need of namespace 

// In each scope, a name can only represent one entity. So, there cannot be two variables with the same name in the same scope. 
// Using namespaces, we can create two variables or member functions having the same name.

int main() 
{ 
	int value; 
	value = 0; 
	double value; // Error here 
	value = 0.0; 
} 
