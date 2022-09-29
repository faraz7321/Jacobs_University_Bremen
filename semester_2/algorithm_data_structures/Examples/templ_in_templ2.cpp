#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template <class T> 
void print1(vector<T> o) {
    unsigned int i;
	for(i = 0; i < o.size(); i++)
		cout << o[i] << " ";
	cout << endl;
}

template <class T, class Alloc, template <class, class> class C>
void print2(C<T, Alloc> o) {
    unsigned int i;
	for(i = 0; i < o.size(); i++)
		cout << o[i] << " ";
	cout << endl;
}

int main() {
    vector<int> v;
	v.push_back(4);
	v.push_back(1);
	v.push_back(12);
	v.push_back(7);
	print1(v);	
    deque<char> d;
    d.push_back('b');
    d.push_back('a');
    d.push_back('c');
    print2(v);
    print2(d);
	return 0;
}
