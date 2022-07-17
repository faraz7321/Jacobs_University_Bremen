#include <initializer_list>
#include <iostream>
#include <algorithm>

using namespace std;

class MyVec {
public:
	int* a;
	MyVec(initializer_list<int> seq) //: a {new int[seq.size()]}
	{
		a = new int[seq.size()];
		copy(seq.begin(), seq.end(), a);
	}
};

int main() {
	MyVec fib{0, 1, 1, 2, 3, 5, 8};
	
	cout << fib.a[0] << " " << fib.a[6] << endl;
	
	return 0;
}
