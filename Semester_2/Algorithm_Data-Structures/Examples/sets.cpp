// Sets/iterators example
#include <set>
#include <vector>
#include <iostream>
//#include <utility>

using namespace std;

const unsigned int size = 20;

class CompareReverse {
	public:
		bool operator() (const int &v1, const int &v2) {
			return v1>v2;
		}
};

int main(int argc, char** argv)
{
	vector<int> vint;
	set<int> sint;  //  a set of ints
	unsigned int i;

	for (i = 0; i < size; i++) {
		vint.push_back(i*i);	// pushes squares in the vector
		sint.insert(i);			// pushes ints in the set
	}
	
	set<int>::iterator it;
	for(it = sint.begin(); it != sint.end(); it++)
		cout << *it << " ";
	cout << endl;

	pair<set<int>::iterator, bool> result;// insert returns a pair: an interator
  										// pointing to the inserted 
	// element and a bool indicating if insertion succeeded or not
	for (i = 0; i < vint.size(); i++) {
		result = sint.insert(vint[i]);	// pushes squares into the set: 
										// some insertion will fail because would 
										// end up in duplicated elements
		if (!result.second)
			cout << "Failed to insert " << vint[i] << endl;
	}
	for(it = sint.begin(); it != sint.end(); it++)
		cout << *it << " ";
	cout << endl;
	
	cout << "Set with reverse functor:" << endl;
	set<int, CompareReverse> sr;
	for(i=0; i < size; i++)
		sr.insert(i);
	for(it = sr.begin(); it != sr.end(); it++)
		cout << *it << " ";
	cout << endl;
}
