#include <iostream>

using namespace std;

int main()
{
    // version 1: the type is corresponding function pointer
    // typedef int (*fp)(int, int);
    // fp myAdd = [] (int a, int b) { return a + b; };
    
    // version 2: using auto
    auto myAdd = [] (int a, int b) { return a + b; };
    cout << "myAdd(1, 2)=" << myAdd(1, 2) << endl;
    
    for(int i=0; i<10; i++) {
        // auto myX = [] () -> int {int a=5, b=7; return a+b;};  // no capture
        // auto myX = [i] () -> int {return i+3;};  // capture i by value
        // auto myX = [=] () -> int {return i+3;};  // capture all by value
        // auto myX = [&i] () -> int { i=i+5; return i+3;};  // capture i by reference
        auto myX = [&] () -> int { i=i+5; return i+3;};  // capture all by reference
        cout << "my mod add = " << myX() << endl;
    }
    return 0;
}
