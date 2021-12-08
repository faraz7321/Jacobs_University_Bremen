/*
CH-230-A
minheritance2.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
using namespace std;

class A
{
    int x;

public:
    A() { x = 20; }
    A(int i) { x = i; }
    void print() { cout << x; }
};

class B : virtual public A
{
public:
    B() : A(10) {}
};

class C : virtual public A
{
public:
    C() : A(10) {}
};

class D : public B, public C
{
public:
    D() : A(10) {}
};

int main()
{
    D d;
    d.print();

    return 0;
}
/* Error:
*   minheritance2.cpp: In function 'int main()':
    minheritance2.cpp:40:7: error: use of deleted function 'D::D()'
    40 |     D d;
       |       ^
    minheritance2.cpp:32:7: note: 'D::D()' is implicitly deleted
    because the default definition would be ill-formed:
    32 | class D : public B, public C
       |       ^
    minheritance2.cpp:32:7: error: no matching function for call to 'A::A()'
    minheritance2.cpp:16:5: note: candidate: 'A::A(int)'
    16 |     A(int i) { x = i; }
       |     ^
    minheritance2.cpp:16:5: note:   candidate expects 1 argument, 0 provided
    minheritance2.cpp:10:7: note: candidate: 'constexpr A::A(const A&)'
    10 | class A
       |       ^
    minheritance2.cpp:10:7: note:   candidate expects 1 argument, 0 provided
    minheritance2.cpp:10:7: note: candidate: 'constexpr A::A(A&&)'
    minheritance2.cpp:10:7: note:   candidate expects 1 argument, 0 provided
*/

/* Fix:
    add a default constructor to A class
    add a default constructor to D class
    constructor of D class will use
    the A class constructor to acheive
    the goal

 */