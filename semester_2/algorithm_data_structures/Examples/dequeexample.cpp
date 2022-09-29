#include <vector>
#include <deque>
#include <iostream>

using namespace std;

/* 
In this example we play with vectors and deques, moving data from one
to the other 
*/

const unsigned int size = 20;

int main(int argc,char** argv)
{
	vector<int> vint;  // a vector of ints
	deque<int> dint;   // a deque of ints
	unsigned int i;

	for (i = 0; i < size; i++)	// fills the vector with 0 1 2 .... 19 by using the push_back member function
		vint.push_back(i);

	// squeeze vectors elements into deque
	for (i = 0; i < vint.size(); i++)	
		// odd numbers pushed to the end, even to the front
		// try to understand what this is doing
		// by translating into if-clause
    	(i % 2) == 0 ? dint.push_front(vint[i]) : dint.push_back(vint[i]);

	for (i = 0; i < dint.size(); i++)	// prints data to the screen
		cout << dint[i] << " ";			// uses the overloaded [] operator
  
	dint.clear();						// removes all the elements
	cout << endl << "How many? " << dint.size() << endl; 	// size will return 0
	cout << "Empty? " << dint.empty() << endl;				// empty will return true
}
