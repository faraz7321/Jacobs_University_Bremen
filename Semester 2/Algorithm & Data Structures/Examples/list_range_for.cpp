#include <string>
#include <list>
#include <iostream>

using namespace std;

int main() {
	list<string> a;
	string x;
	while (true) {
		cin >> x;
		if (x.compare("ZZ") == 0) break;
		a.push_back(x);
	}
	// version 1: use auto
	// for (auto el : a) // access by value using copies, cannot change items
	// for (auto& el: a) // access by reference without copies, can change items
	// for (auto const & el: a) // acces by reference without copies, without changing items
	
	// version 2: element is of type string
	for(string el : a)
		cout << el  << endl;
		
	return 0;	
}

