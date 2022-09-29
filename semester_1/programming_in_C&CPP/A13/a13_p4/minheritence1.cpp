/*
CH-230-A
minheritence1.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
using namespace std;

class A
{
protected:
    int x;

public:
    void setX(int i) { x = i; }
    void print() { cout << x; }
};

class B : public virtual A
{
public:
    B() { setX(10); }
};

class C : public virtual A // Add virtual keyword
{
public:
    C() { setX(20); }
};

class D : public B, public C // Add virtual keyword
{
};

int main()
{
    D d;
    d.print(); // error: request for member 'print' is ambiguous
    return 0;
}
/*
diamond problem
D object cannot call print() because the function is
present in both B and C
class B and C need to be virtual classes
so D can inherit both of of them

*/
