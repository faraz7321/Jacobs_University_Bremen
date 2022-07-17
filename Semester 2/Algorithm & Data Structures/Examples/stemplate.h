#include <iostream>

template <class T>
class Test {
	private:
		T prop;
	public:
		Test(T);
		void print();
};

// Solution 1: equivalent with writing the class and its method definitions in one header file
//#include "stemplate.cpp"

