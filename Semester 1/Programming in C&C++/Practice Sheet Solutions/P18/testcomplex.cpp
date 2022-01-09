#include<iostream>
#include "complex.h"
using namespace std;

int main()
{
    Complex z1(3,4);
    Complex z2(3);

    cout << z1 << endl << z2 << endl;

    cout << (z1<z2);
    return 0;
}
