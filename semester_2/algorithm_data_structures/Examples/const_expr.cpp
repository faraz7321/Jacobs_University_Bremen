#include <iostream>

using namespace std;

constexpr int fib(int n) {
	return (n < 2) ? n : (fib(n-2) + fib(n - 1));
}

int main() {
    int fibnum;
    cin >> fibnum;
    int arr1[fib(fibnum)];
    int arr2[fib(3)];
    cout << fib(fibnum) << endl;
    cout << fib(3) << endl;
	cout << "Size of arr " << sizeof(arr1) << endl;
	cout << "Size of arr " << sizeof(arr2) << endl;
	return 0;
}
