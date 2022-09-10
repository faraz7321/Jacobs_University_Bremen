#include <iostream>

using namespace std;

class Complex {
	private:
		double re, im;
	public:
		Complex(double re, double im) {
			this->re = re;
			this->im = im;
		}
		Complex& operator=(const Complex o) {
			this->re = o.re;
			this->im = o.im;
			return *this;
		}
		Complex operator+(const Complex o) {
			return Complex(this->re + o.re, this->im + o.im);
		}
		friend ostream& operator<<(ostream &o, Complex c) {
			o << c.re << "+" << c.im << "i" << endl;
			return o;
		}
};

template <class T>
T array_sum(T arr[], int size) {
	int i;
	T sum = arr[0];
	for (i = 1; i < size; i ++) {
		sum = sum + arr[i];
	}
	return sum;
}

int main() {
	int intarr[] = {1, 2, 3, 4, 5, 6};
	cout << array_sum(intarr, 6) << endl;

	double darr[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
	cout << array_sum(darr, 6) << endl;

	string sarr[] = {"apple", "cherry", "orange"};
	cout << array_sum(sarr, 3) << endl;
	
	Complex carr[] = {Complex(1, 2), Complex(3, 4), Complex(-3, -5)};
	cout << array_sum(carr, 3) << endl;
}


