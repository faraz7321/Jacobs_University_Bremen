#include <vector>
#include <list>
#include <iostream>

using namespace std;

const unsigned int size = 20;

/* 
Illustrates how we can move data from vectors to lists by using the push_back 
and push_front member functions
*/

int main(int argc, char** argv) {
	vector<int> vint;
	list<int> lint;
	unsigned int i;

	for (i = 0; i < size; i++)
		vint.push_back(i);

	// squeeze vectors elements into list
	for (i = 0; i < vint.size(); i++)
  		// translate to if...
		(i % 2) == 0 ? lint.push_front(vint[i]) : lint.push_back(vint[i]);

	lint.sort();

	while (!lint.empty()) {
		cout << lint.front() << " ";
		lint.pop_front();
	}
	cout << endl;
}
