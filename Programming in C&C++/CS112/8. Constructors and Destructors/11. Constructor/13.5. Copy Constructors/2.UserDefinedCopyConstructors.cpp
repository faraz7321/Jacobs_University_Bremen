/**********************************************************************
 * Following is a complete C++ program to demonstrate use of Copy     *
 * constructor. In the following String class, we must write copy     *
 * constructor.                                                       *
 **********************************************************************/

#include<iostream>
#include<cstring>
using namespace std;

class String {
private:
	char *s;
	int size;
public:
	String(const char *str = NULL) { // constructor
		size = strlen(str);
		s = new char[size+1];
		strcpy(s, str);
	}

	~String() { delete [] s; }// destructor
	
	String(const String& old_str) { // copy constructor
		size = old_str.size;
		s = new char[size+1];
		strcpy(s, old_str.s);
	}
	void print() { cout << s << endl; } // Function to print string
	
	void change(const char * str) { // Function to change
		delete [] s;
		size = strlen(str);
		s = new char[size+1];
		strcpy(s, str);
	}
};

int main() {
	String str1("Covid19 Long holidays");
	String str2 = str1;

	str1.print(); // what is printed ?
	str2.print();

	str2.change("CS112 Computer Programming Mid Term & Project ");

	str1.print(); // what is printed now ?
	str2.print();
	return 0;
}
