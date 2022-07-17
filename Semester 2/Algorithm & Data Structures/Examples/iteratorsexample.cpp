#include <vector>
#include <list>
#include <deque>
#include <iostream>

using namespace std;

const unsigned int size = 20;

int main(int argc, char** argv)
{
	vector<int> vint;
	list<int> lint;
	deque<int> dint;
	for (unsigned int i = 0; i < size; i++) {
		vint.push_back(i);
		lint.push_front(i * i);
		(i % 2) == 0 ? dint.push_front(i) : dint.push_back(i);
	}

	vector<int>::iterator viter = vint.begin();
	list<int>::iterator liter;
	deque<int>::iterator diter = dint.begin();
  
  	while (viter != vint.end()) {
		cout << *viter << " " ;
		viter++;
	}
  
	cout << endl;

	while (diter != dint.end()) {
		cout << *diter << " ";
		diter++;
	}
  
	cout << endl;
  
	for (liter = lint.begin(); liter != lint.end(); liter++)
		cout << *liter << " ";
}
