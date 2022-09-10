#include <iostream>
#include <vector>
#include <list>

using namespace std;
int main() {

	list<int> la;
	list<int> lb;
	vector<list<int>> v;

	la.push_back(1);
	la.push_back(2);
	la.push_back(3);
	
	lb.push_back(4);
	lb.push_back(5);
	lb.push_back(6);

	v.push_back(la);
	v.push_back(lb);

	// Version 1: using iterators
	vector<list<int>>::iterator itvec;
	for(itvec=v.begin(); itvec!=v.end(); itvec++) {
		list<int>::iterator itlist;
		//cout << "Outer loop: " << *itvec << endl;
		for(itlist=itvec->begin(); itlist!=itvec->end(); itlist++)
			cout << *itlist << " ";
		cout << endl;
	}
	vector<vector<int>> vv;
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	vector<int> v2;
	v2.push_back(3);
	v2.push_back(4);
	vv.push_back(v1);
	vv.push_back(v2);

	// Version 2: using [] operator
	for(unsigned int i=0; i<vv.size(); i++) {
		for(unsigned int j=0; j<vv[i].size(); j++)
			cout << vv[i][j] << " ";
		cout << endl;
	}

	// Version 3: using range for
	for(auto outel : vv) {
		for(auto inel : outel) 
			cout << inel << " ";
		cout << endl;
	}
	return 0;
}


