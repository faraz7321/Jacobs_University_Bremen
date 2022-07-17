#include <iostream>
#include <tuple>

using namespace std;

int main() {
	tuple<int, double, char> tp{41, 3.14, 'x'};
	cout << get<1>(tp) << endl;
	cout << get<2>(tp) << endl;
	cout << get<0>(tp) << endl;
	// you can change the content of the tuple
	get<0>(tp) = 100;
	cout << get<0>(tp) << endl;
}
	
