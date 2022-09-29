#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

int main() {
	vector<int> myVecInt={1};
	vector<double> myDoubleInt={1.1};

	// automatically determines needed type
	decltype(myVecInt[0]*myDoubleInt[0]) myDouble = 2.1;
	cout << typeid(myDouble).name() << endl;
}

