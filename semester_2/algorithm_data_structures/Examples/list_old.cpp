#include <string>
#include <list>
#include <iostream>

using namespace std;

int main() {
	list<string> a;
	list<string>::iterator iter;
	string x;
	while (true) {
		cin >> x;
		if (x.compare("ZZ") == 0) break;
		a.push_back(x);
	}

	for (iter = a.begin(); iter != a.end(); iter++) {
		cout << *iter  << endl;
	}
}

