#include <iostream>
#include <set>

using namespace std;

template <typename T> 
void print(set<T> o) {
	typename set<T>::iterator it;
	for(it = o.begin(); it != o.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int main() {
	set<int> s;
	s.insert(4);
	s.insert(1);
	s.insert(12);
	s.insert(7);
	print<int>(s);	
	return 0;
}
