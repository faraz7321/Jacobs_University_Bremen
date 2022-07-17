#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename... T>
int f(T... args) {
	return (sizeof... (args));
}

template<typename T>
void printCommaSeparatedList(T value)
{
	cout << value << endl;
}

template<typename First, typename ... Rest>
void printCommaSeparatedList(First first, Rest ... rest)
{
	cout << first << ", ";
	printCommaSeparatedList(rest...);
}


int main() {
	cout << "\n";

	auto intList= {1, 2, 3};
	vector <int> intVec= {1, 2, 3, 4, 5};

	cout << "f() has " << f<double>(1.4, 5.8) << " arguments\n";
	cout << "f() has " << f<double>(1.4, "fadfa", 'r') << " arguments\n";
	cout << "f(42, 3.14) has " << f(42, 3.14) << " arguments\n";
	cout << "f(\"one\", \"two\", \"three\", \"four\") has " << f("one", "two", "three", "four" ) << " arguments\n";
	cout << "f(intVec,intList) has " << f(intVec, intList) << " arguments\n\n";
    
	printCommaSeparatedList("Only primary template used.");
	printCommaSeparatedList(42, "hello", 2.3, 'a');
	cout << "\n";
}

